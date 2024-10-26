#ifndef SORTEARJUGADORES_H_INCLUDED
#define SORTEARJUGADORES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../estructuras.h"
#include "../TDA_LISTA/lista.h"

int sortearJugadores(tLista *lista);
tNodo* obtenerNodoEnIndice(tLista *lista, int indice);

#endif // SORTEARJUGADORES_H_INCLUDED