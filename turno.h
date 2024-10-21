#ifndef TURNO_H_INCLUDED
#define TURNO_H_INCLUDED

#include <pthread.h>// Para usar hilos..por lo que averigue deberia funcionar en linux
#include <windows.h>// Solo se uso para el manejo del buffer del teclado de consola...investigar si existe otra manera que sea mas estandar

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

#include "LIBS/VALIDACION_RESP/validacionResp.h"
#include "LIBS/TDA_LISTA/lista.h"

#define TODO_OK 1;

//Datos para usar con cronometro "Hilos"
typedef struct {
    unsigned int* tiempo_turno;
    int* continuar;
} Datos;

typedef struct
{
	char nombre_jugador[16];
	int puntos;
}tJugador;

//tRonda es necesario para llevar registro de cada movimiento del jugador
typedef struct
{
	unsigned int vidas_total;
	unsigned int vidas_consumidas;
	unsigned int puntos_turno;
}tRonda;

typedef struct
{
	char nivel; // F = facil, N = normal, D = dificil
	unsigned int tiempo_muestra;
	unsigned int tiempo_turno;
	unsigned cant_vidas;
}tConfig;

/**FUNCION PRINCIPAL QUE GESTIONA EL TURNO DE CADA JUGADOR*/
int turnoJugador(tJugador* jugador_actual, tConfig config_partida);

/**Solo muestra la ronda que esta por empezar*/
void mostrarRonda(int ronda);

/**Esta funcion SIMULA una solicitud de UN solo numero a la api, hace la conversion del numero al caracter o color asociado y lo almacena al final de la lista
    -Solo se le debe pasar como argumento la lista donde se guardara lo que solicite de la api.
    -"Lista* sec_ya_generada" Solo esta para generar los lotes de prueba.
*/
int generarSecuencia(tLista* sec_ya_generada, tLista* sec);

/**Esta funcion sirve para que el jugador ingrese letra por letra su respuesta en la lista en un determinado tiempo */
int respuestaJugador(tLista* l, unsigned int tiempo_turno);

/** Funcion de cronometro que sera ejecutada por los hilos */
void* cronometro(void* args);

void limpiarBufferTeclado();

/** Funcion para preguntar al usuario cuantas vidas quiere usar.
    -Se mandan como argumentos el rango de vidas disponibles
*/
int cuantasVidasUsar(int min, int max);

/**Funciones encargadas de procesar las respuestas :
    -Tambien se le debe pasar el puntero FILE para que se registren los movimientos del turno
*/
void respuestaCorrecta(tJugador* jugador, tLista* l_resp, tRonda* rondaJuego);
void respuestaIncorrecta(tLista* l_resp, tRonda* rondaJuego, int cant_car_resp);
void usoCaracterEspecial(tLista* l_resp, tLista* l_sec, tRonda* rondaJuego, unsigned tiempo_muestra ,int cant_car_resp);
void noContesta(tRonda* ronda_juego, tLista* sec, unsigned tiempo_muestra);

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
