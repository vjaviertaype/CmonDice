#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <windows.h>

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
int eliminarNUltimos(tLista* l,unsigned cantBytes,int cantElim);

/**Esta funcion muestra una lista elemento por elemento por un determinado tiempo */
int mostrarSecuenciaXTiempo(tLista* l, unsigned int tiempo_muestra, Mostrar mostrar);

/** Compara listas, si son iguales retorna 1, si son distintas retorna 0*/
int listasIguales(tLista* l_sec, tLista* l_resp,Cmp cmp);

/** Inserta de forma Ordenada en una lista segun un criterio dado por un comparador**/
//int insertarOrdenado(tLista *l, const void *dato, unsigned cantBytes, Cmp comparar);

int insertarOrdenado(tLista* l, void* dato, unsigned cantBytes, Cmp cmp, bool duplicado, bool ordenAsc);

#endif // LISTA_H_INCLUDED
