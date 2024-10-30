#ifndef GANADORES_H_INCLUDED
#define GANADORES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../TDA_PILA/pila.h"
#include "../../estructuras.h"
#include "../comun.h"
#include "../ART/arte.h"

#define PRIMER_INGRESO 1
#define JUGADOR_SIN_PUNTOS -1
#define JUGADOR_NO_SUPERA_MAYOR_PUNTAJE -2
#define NO_HUBO_GANADORES 0
#define HUBO_GANADOR 1

int cargarPilaGanadores(tPila* pilaG, tJugador* jugador, Cmp cmp);
int mostrarGanadores(tPila* pilaG);

#endif // GANADORES_H_INCLUDED
