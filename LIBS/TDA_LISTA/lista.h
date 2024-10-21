#ifndef LISTA_H_
#define LISTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "../comun.h"

/**PRIMITIVAS ELEMENTALES**/

void crearLista(tLista* l);

int listaVacia(const tLista* l);

int listaLLena(const tLista* l, unsigned cantBytes);

void vaciarLista(tLista* l);

int ponerAlComienzo(tLista* l, const void* dato, unsigned cantBytes);

int sacarPrimeroLista(tLista* l, void* dato, unsigned cantBytes);

int verPrimeroLista(const tLista* l, void* dato, unsigned cantBytes);

int ponerAlFinal(tLista* l, const void* dato, unsigned cantBytes);

int sacarUltimoLista(tLista* l, void* dato, unsigned cantBytes);

int verUltimoLista(const tLista* l, void* dato, unsigned cantBytes);

void mapLista(tLista* l, void* contexto, Accion accion);

int eliminarNUltimos(tLista* l,unsigned cantBytes ,int cantElim);

/**Esta funcion muestra una lista elemento por elemento por un determinado tiempo */
int mostrarSecuenciaXTiempo(tLista* l, unsigned int tiempo_muestra, Mostrar mostrar);

/** Compara listas, si son iguales retorna 1, si son distintas retorna 0*/
int listasIguales(tLista* l_sec, tLista* l_resp,Cmp cmp);

#endif // LISTA_H_
