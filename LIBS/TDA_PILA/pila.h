/*** PILA-DINAMICA-.H ***/
#ifndef PILA_H_
#define PILA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../comun.h"

typedef tNodo * tPila;

void crearPila(tPila* p);
int pilaLLena(const tPila* p, unsigned cantBytes);
int ponerEnPila(tPila* p, const void* dato, unsigned cantBytes);
int verTope(const tPila* p, void* dato, unsigned cantBytes);
int pilaVacia(const tPila* p);
int sacarDePila(tPila* p, void* dato, unsigned cantBytes);
void vaciarPila(tPila* p);

#endif // PILA_H_


///*** PILA-ESTATICA-.H ***/
//
//#ifndef PILA_H_
//#define PILA_H_
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define minimo( X , Y )  ( (X) <= (Y) ? (X) : (Y) )
//
//#define TAM_PILA 340
//
//typedef struct
//{
//    char pila[TAM_PILA];
//    unsigned tope;
//} tPila;
//
//void crearPila(tPila* p);
//int pilaLLena(const tPila* p, unsigned cantBytes);
//int ponerEnPila(tPila* p, const void* dato, unsigned cantBytes);
//int verTope(const tPila* p, void* dato, unsigned cantBytes);
//int pilaVacia(const tPila* p);
//int sacarDePila(tPila* p, void* dato, unsigned cantBytes);
//void vaciarPila(tPila* p);
//
//
//#endif // PILA_H_
