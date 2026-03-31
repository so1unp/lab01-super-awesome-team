#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    unsigned char block[8];
    ssize_t bytes_read;

    // Leer bloques de 8 bytes: 7 aleatorios + 1 byte del mensaje original
    while ((bytes_read = read(STDIN_FILENO, block, sizeof(block))) > 0) {
        if (bytes_read < 8) {
            perror("read: bloque incompleto");
            exit(EXIT_FAILURE);
        }
        // El byte del mensaje es el último (índice 7)
        if (write(STDOUT_FILENO, &block[7], 1) != 1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
