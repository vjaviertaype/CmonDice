#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../comun.h"

#define CANT_MAX_CONFIG 3
#define TODO_OK 1
#define SIN_MEM -1
#define ERROR_ARCH -2
#define EXIT -141
#define NON_VALID -142


typedef struct
{
    char nivel; // F = fácil, N = normal, D = difícil
    unsigned int tiempo_muestra;
    unsigned int tiempo_turno;
    unsigned cant_vidas;
} tConfig;

int cargarConfig(const char *, tConfig *, unsigned);
int validarConfig(tConfig *);
void mostrarConfig(tConfig *);
int seleccionaConfigIndice(const char *[], unsigned);

#endif // CONFIG_H_INCLUDED
