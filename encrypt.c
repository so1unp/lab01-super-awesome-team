#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

/* Cantidad de bytes aleatorios que preceden a cada byte real en la salida */
#define RANDOM_BYTES_COUNT 7

/*
 * encrypt_byte: encripta un único byte.
 *
 * Formato del bloque de salida (8 bytes en total):
 *   [ r0 ][ r1 ][ r2 ][ r3 ][ r4 ][ r5 ][ r6 ][ c ]
 *     <--- 7 bytes aleatorios de relleno --->   dato
 *
 * El receptor sabe que el byte real siempre está en la posición 7,
 * por lo que puede descartar los anteriores sin conocer la semilla.
 */
void encrypt_byte(unsigned char c) {
    unsigned char buffer[RANDOM_BYTES_COUNT + 1];

    /* Llenar las primeras 7 posiciones con bytes pseudo-aleatorios */
    for (int i = 0; i < RANDOM_BYTES_COUNT; i++) {
        buffer[i] = (unsigned char)(rand() % 256);
    }

    /* La posición 7 lleva el byte original del mensaje */
    buffer[RANDOM_BYTES_COUNT] = c;

    /* Escribir el bloque completo de 8 bytes en stdout de una sola vez */
    if (write(STDOUT_FILENO, buffer, RANDOM_BYTES_COUNT + 1) == -1) {
        perror("Error al escribir en stdout");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    /* Inicializar la semilla con el tiempo actual para que los bytes
     * aleatorios sean distintos en cada ejecución del programa */
    srand(time(NULL));

    /* CASO 1: El mensaje viene como argumento de línea de comando
     * Ejemplo: bin/encrypt "hola mundo" */
    if (argc > 1) {
        char *message = argv[1];
        /* Recorrer el string carácter a carácter hasta el terminador '\0' */
        for (int i = 0; message[i] != '\0'; i++) {
            encrypt_byte((unsigned char)message[i]);
        }
    }
    /* CASO 2: No hay argumento, leer desde la entrada estándar
     * Ejemplo: bin/encrypt < archivo.txt   o   echo hola | bin/encrypt */
    else {
        unsigned char buffer;
        ssize_t bytes_read;

        /* Leer un byte a la vez hasta EOF (bytes_read == 0) o error (-1) */
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