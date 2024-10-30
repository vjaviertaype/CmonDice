#ifndef TURNO_H_INCLUDED
#define TURNO_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

#include "LIBS/CONFIG/config.h"
#include "LIBS/ARCHIVO/archivo.h"
#include "LIBS/VALIDACION_RESP/validacionResp.h"
#include "LIBS/TDA_LISTA/lista.h"
#include "LIBS/API/api.h"
#include "estructuras.h"
#include "LIBS/MENU/menu.h"

/**FUNCION PRINCIPAL QUE GESTIONA EL TURNO DE CADA JUGADOR*/
int turnoJugador(FILE *info, tJugador* jugador_actual, tConfig config_partida, CURL*curl, const char*url);

/**Solo muestra la ronda que esta por empezar*/
void mostrarRonda(int ronda);

/**Solicitud api*/
int generarSecuencia(tLista* sec, CURL *curl, const char*url);

/**Esta funcion sirve para que el jugador ingrese letra por letra su respuesta en la lista en un determinado tiempo */
int respuestaJugador(tLista* l, unsigned int tiempo_turno);

/** Funcion para preguntar al usuario cuantas vidas quiere usar.
    -Se mandan como argumentos el rango de vidas disponibles
*/
int cuantasVidasUsar(int maximo);

/**Funciones encargadas de procesar las respuestas :
    -Tambien se le debe pasar el puntero FILE para que se registren los movimientos del turno
*/
void respuestaCorrecta(FILE*info, tJugador* jugador, tLista* l_sec, tLista* l_resp, tRonda* ronda_juego);
void noContesta(FILE*info, tLista* l_sec, tLista* l_resp, tRonda* ronda_juego, unsigned tiempo_muestra);
void usoCaracterEspecial(FILE*info, tLista* l_sec, tLista* l_resp, tRonda* ronda_juego, unsigned tiempo_muestra ,int cant_car_resp);
void respuestaIncorrecta(FILE*info, tLista* l_sec, tLista* l_resp, tRonda* ronda_juego, int cant_car_resp);
void mostrarSecuenciaXTiempo(tLista *l_sec,unsigned tiempo_muestra,const char *mensaje);

///Funciones que se usan como puntero a funcion..
void mostrarCaracter(void* e);

#endif // TURNO_H_INCLUDED
