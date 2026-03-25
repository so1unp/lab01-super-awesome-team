[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/s3gLwsY4)
# Laboratorio 1 - Encriptador / Desencriptador
El objetivo de este laboratorio es familiarizarse con el lenguaje C, las herramientas de desarrollo y las llamadas al sistema en Linux.

## Enunciado
Completar los programas `encrypt.c` y `decrypt.c` para que encripten y desencripten un mensaje respectivamente.

La encriptación es muy sencilla: cada byte del mensaje debe ser precedido por 7 bytes aleatorios en el resultado encriptado.

### Llamadas al sistema a utilizar

Utilizar las siguientes llamadas al sistema:

- [`write()`](http://man7.org/linux/man-pages/man2/write.2.html): escribe *n* bytes en el descriptor de archivo indicado.
- [`read()`](http://man7.org/linux/man-pages/man2/read.2.html): lee _n_ bytes desde el descriptor de archivo indicado.

También usar las siguientes funciones de biblioteca:

- [`rand()`](https://www.man7.org/linux/man-pages/man3/rand.3.html): retorna un número pseudo-aleatorio.
- [`srand()`](https://www.man7.org/linux/man-pages/man3/rand.3.html): inicializa semilla para generación de números pseudo-aleatorios.
- [`perror()`](https://www.man7.org/linux/man-pages/man3/perror.3.html): para imprimir mensajes de error por fallos en invocaciones a llamadas al sistema u otras funciones de biblioteca.

### Encriptador
El programa `encrypt.c` debe leer el mensaje a encriptar como un argumento desde la línea de comando o desde la _entrada estándar_ y generar el contenido encriptado en la _salida estándar_:

- Encripta "hola" y lo imprime por la salida estándar: `bin/encrypt hola`
- Encripta el archivo `topsecret.txt`: `bin/encrypt < topsecret.txt`

Utilizar `argv` y `argc` para determinar si el mensaje a encriptar es provisto como argumento.

A continuación un ejemplo de que tendría que devolver el programa al encriptar "hola" y enviarlo a la salida estándar. El programa `xxd` muestra una reprsentación hexadecimal de su entrada y lo usamos para que la salida sea más fácil de leer:
```
$ bin/encrypt "hola" | xxd
00000000: 2b07 7d09 250e 5e68 5c17 2b2c 0c17 5b6f  +.}.%.^h\.+,..[o
00000010: 1829 0100 5f26 186c 247d 1f15 087b 4061  .).._&.l$}...{@a
```

### Desencriptador
El programa `decrypt.c` debe leer los datos encriptados desde la *entrada estándar*. El mensaje oculto es presentado en la _salida estándar_. El número de bytes leído de la entrada estándar indica la longitud del mensaje oculto.

### Ejecución

Dado que ambos programan pueden leer y escribir de la entrada estándar, tendrían que poder ejecutar un comando como el siguiente:
```
$ bin/encrypt hola | bin/decrypt
hola
$
```

O incluso así, pasando el mensaje desde la entrada estándar:
```
$ echo -n hola | bin/encrypt | bin/decrypt
hola
$
```

---

¡Fín del Laboratorio 1!
