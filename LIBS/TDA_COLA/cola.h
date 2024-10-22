/***COLA-DINAMICA-.H ***/

#ifndef COLA_H_
#define COLA_H_

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

#endif // COLA_H_

///***COLA-ESTATICA-.H ***/
//
//#ifndef COLA_H_
//#define COLA_H_
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define minimo(a,b) ((a)<(b)?(a):(b))
//
//#define TAM_COLA 300
//
//typedef struct
//{
//    char cola[TAM_COLA];
//    unsigned pri;
//    unsigned ult;
//    unsigned tamDisp;
//} tCola;
//
//void crearCola(tCola *cola);
//
//int colaLena(const tCola *cola, unsigned cantBytes);
//
//int ponerEnCola(tCola *cola, const void *dato, unsigned cantBytes);
//
//void vaciarCola(tCola *cola);
//
//int colaVacia(const tCola *cola);
//
//int sacarDeCola(tCola *cola, void *dato, unsigned cantBytes);
//
//#endif // COLA_H_
