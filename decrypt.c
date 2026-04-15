#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * decrypt: lee datos encriptados desde stdin y escribe el mensaje
 * original en stdout.
 *
 * Protocolo esperado en la entrada (producido por encrypt):
 *   Por cada byte del mensaje original hay un bloque de 8 bytes:
 *   [ r0 ][ r1 ][ r2 ][ r3 ][ r4 ][ r5 ][ r6 ][ dato ]
 *     <--- 7 bytes de relleno aleatorio --->      real
 *
 * Este programa descarta los 7 bytes de relleno y conserva solo
 * el byte en la posición 7 de cada bloque.
 */
int main(int argc, char *argv[])
{
    unsigned char block[8]; /* buffer para un bloque de 8 bytes */
    ssize_t bytes_read;

    /* Leer bloques de 8 bytes mientras haya datos en stdin */
    while ((bytes_read = read(STDIN_FILENO, block, sizeof(block))) > 0) {
        /* Si se leyeron menos de 8 bytes el stream está incompleto o corrupto */
        if (bytes_read < 8) {
            perror("read: bloque incompleto");
            exit(EXIT_FAILURE);
        }
        /* Escribir únicamente el byte real (posición 7), ignorando el relleno */
        if (write(STDOUT_FILENO, &block[7], 1) != 1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    /* bytes_read == 0 indica EOF (fin normal); -1 indica error de lectura */
    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
