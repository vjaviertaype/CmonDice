#ifndef TURNO_H_INCLUDED
#define TURNO_H_INCLUDED

#include <windows.h>// Solo se uso para el manejo del buffer del teclado de consola...investigar si existe otra manera que sea mas estandar

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

/**Esta funcion SIMULA una solicitud de UN solo numero a la api, hace la conversion del numero al caracter o color asociado y lo almacena al final de la lista
    -Solo se le debe pasar como argumento la lista donde se guardara lo que solicite de la api.
    -"Lista* sec_ya_generada" Solo esta para generar los lotes de prueba.
*/
int generarSecuencia(tLista* sec, CURL *curl, const char*url);

/**Esta funcion sirve para que el jugador ingrese letra por letra su respuesta en la lista en un determinado tiempo */
int respuestaJugador(tLista* l, unsigned int tiempo_turno);

void limpiarBufferTeclado();

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

///Funciones que se usan como puntero a funcion..
void contarCantidad(void* e, void* contexto);
void mostrarCaracter(void* e);

///Limpia la pantalla
void limpiarPantalla();

///Hace una pausa
void pausa();

/** Funcion encargada de hacer el lote de pruebas...luego BORRAR*/
int generarSecuenciaParaPruebas(tLista* lista);

#endif // TURNO_H_INCLUDED
