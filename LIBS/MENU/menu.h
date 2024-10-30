#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#define NOMBRE_CONFIG "config.txt"
#define URL "https://www.random.org/integers/?num=1&min=1&max=4&col=1&base=10&format=plain&rnd=new"

#include "../comun.h"
#include "../CONFIG/config.h"
#include "../ARCHIVO/archivo.h"
#include "../VALIDACION_RESP/validacionResp.h"
#include "../TDA_LISTA/lista.h"
#include "../API/api.h"
#include "../../estructuras.h"
#include "../SORTEAR_JUG/sortearJugadores.h"
#include "../../turno.h"
#include "../MUSICA/musica.h"
#include "../TDA_PILA/pila.h"
#include "../GANADORES/ganadores.h"

void mostrarInstrucciones();
int menuPrincipal(CURL *curl);

int jugar(CURL *);
void mostrarJugador(void *e);
void mostrarTurnoJugador(tJugador *pj);
int menuIngresoJugador(tJugador *pj,int);
int ingresoDeJugadores(tLista *l);
int compararPuntajeJugador(const void *a, const void *b);
int compararEnteros(const void *a, const void *b);
void desarrolladores();
void verDificultad(tConfig *);
void volverAtras();
#endif // MENU_H_INCLUDED
