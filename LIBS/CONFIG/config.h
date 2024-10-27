#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "../comun.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
void mostrarConfig(int, tConfig *);
int seleccionaConfigIndice(tConfig *, unsigned);
#endif // CONFIG_H_INCLUDED
