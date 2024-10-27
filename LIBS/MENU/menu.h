#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#define NOMBRE_CONFIG "config.txt"
#define DIFICULTAD_SELECCIONADA 1
#define URL "https://www.random.org/integers/?num=1&min=1&max=4&col=1&base=10&format=plain&rnd=new"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "../CONFIG/config.h"
#include "../ARCHIVO/archivo.h"
#include "../VALIDACION_RESP/validacionResp.h"
#include "../TDA_LISTA/lista.h"
#include "../TDA_COLA/cola.h"
#include "../API/api.h"
#include "../../estructuras.h"
#include "../SORTEAR_JUG/sortearJugadores.h"
#include "../../turno.h"
#define UP_ARROW 72
#define DOWN_ARROW 80
#define ESCAPE 27

typedef void (*FuncPtr)();

void mostrarInstrucciones(CURL*curl);
void limpiarPantalla();
int menuPrincipal();
void displayMenu(const char *options[], int numOptions, int selectedOption);
void gotoxy(int x, int y);
int jugar(CURL *);
void mostrarTurnoJugador(tJugador *pj);
int menuIngresoJugador(tJugador *pj);
int ingresoDeJugadores(tLista *l);
int compararPuntajeJugador(const void *a, const void *b);
int compararEnteros(const void *a, const void *b);
void mostrarTitulo();
void desarrolladores(CURL*);
void verDificultad(CURL*);
void volverAtras(CURL*);
#endif // MENU_H_INCLUDED
