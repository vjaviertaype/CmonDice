#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../comun.h"
#include "../TDA_LISTA/lista.h"
#include "../../estructuras.h"

#define PREFIJO "informe"
#define SEPARADOR "_"
#define EXTENSION ".txt"

#define ABRIR_FALLO -39

FILE* inicializarInforme(const char *nombre);
int generarCabeceraJugador(FILE *info,int pos,char *nombre);
int generarCabezeraRonda(FILE *info,tRonda *ronda_actual);
void guardarRonda(FILE *info,tRonda *ronda_actual,tLista *sec_actual, tLista *respuesta);
void imprimirCaracterEnArchivo(void *caracter,void *archivo);
int finalizarInforme(FILE *info, tLista *p_jugadores, Cmp comparar);

#endif // ARCHIVO_H_INCLUDED
