#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define RANDOM_BYTES_COUNT 7

/**
 * Función auxiliar para encriptar un solo byte:
 * Escribe 7 bytes aleatorios seguidos del byte original.
 */
void encrypt_byte(unsigned char c) {
    unsigned char buffer[RANDOM_BYTES_COUNT + 1];
    
    // Generar 7 bytes aleatorios
    for (int i = 0; i < RANDOM_BYTES_COUNT; i++) {
        buffer[i] = (unsigned char)(rand() % 256);
    }
    
    // El octavo byte es el caracter real
    buffer[RANDOM_BYTES_COUNT] = c;

    // Escribir los 8 bytes a la salida estándar
    if (write(STDOUT_FILENO, buffer, RANDOM_BYTES_COUNT + 1) == -1) {
        perror("Error al escribir en stdout");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    // CASO 1: El mensaje viene como argumento (argv[1])
    if (argc > 1) {
        char *message = argv[1];
        for (int i = 0; message[i] != '\0'; i++) {
            encrypt_byte((unsigned char)message[i]);
        }
    } 
    // CASO 2: Leer desde la entrada estándar
    else {
        unsigned char buffer;
        ssize_t bytes_read;

        // Leer byte por byte hasta el final del archivo (EOF)
        while ((bytes_read = read(STDIN_FILENO, &buffer, 1)) > 0) {
            encrypt_byte(buffer);
        }

        if (bytes_read == -1) {
            perror("Error al leer de stdin");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}