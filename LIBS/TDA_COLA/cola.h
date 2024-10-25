#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../comun.h"

typedef struct
{
    tNodo *pri;
    tNodo *ult;
} tCola;

void crearCola(tCola *cola);

int colaLena(const tCola *cola, unsigned cantBytes);

int ponerEnCola(tCola *cola, const void *dato, unsigned cantBytes);

void vaciarCola(tCola *cola);

int colaVacia(const tCola *cola);

int sacarDeCola(tCola *cola, void *dato, unsigned cantBytes);

int verPrimeroCola(const tCola *cola, void *dato, unsigned cantBytes);

#endif // COLA_H_INCLUDED
