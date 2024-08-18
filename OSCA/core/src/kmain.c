void kmain(void);

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <extras/vector.h>
#include <x86/driver/tty.h>
#include <x86/driver/io.h>

// Función que suma todos los números enteros pasados como argumentos
int sumar_numeros(int cantidad, ...) {
    va_list args;

    // Inicializar va_list con el primer argumento
    va_start(args, cantidad);

    int suma = 0;
    // Sumar todos los argumentos
	size_t i;
    for (i = 0; i < cantidad; i++) {
        suma += va_arg(args, int);
    }

    // Limpiar va_list
    va_end(args);

    return suma;
}

typedef float __alignas(4) flt;

void kmain(void)
{
	/* Initialize terminal interface */
	terminal_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_LIGHT_RED); /* cambio de color funciona bien */
	terminal_initialize(); /* tty (terminal telemetry) funciona bien */
    init_fpu();
	int a = sumar_numeros(2, 4, 6); /* stdarg funciona bien */
    flt *b = (flt*)malloc(sizeof(flt)); /* Al intentar definir una variable float en cualquier funcion, se reinicia el entorno */
    *b = 2.0f;
    free(b);
	printf("%d\n%s\t%s\b", a, "abc", "cba"); /* stdio funciona bien */
}