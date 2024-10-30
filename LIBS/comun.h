#ifndef COMUN_H_INCLUDED
#define COMUN_H_INCLUDED

#include <time.h>
#include <windows.h>

#define minimo(X, Y) ( (X) <= (Y)?(X):(Y) )

typedef struct sNodo
{
    void            *info;
    unsigned        tamInfo;
    struct sNodo    *sig;
}tNodo;
typedef tNodo *tLista;

typedef int (*Cmp)(const void* e1, const void* e2);
typedef void (*Accion)(void* e, void* contexto);
typedef void (*Mostrar)(void* e);

void obtenerFechaDeAhora(char *buffer, unsigned tam);
void limpiarBufferTeclado();
void limpiarPantalla();
void pause();
void mostrarTemporizador(unsigned int tiempo);

/// limpieza de I/O
void limpiarBufferTeclado();
void limpiarPantalla();
/// pausa de terminal
void pausa();

void ocultarCursor();
void mostrarCursor();

void mostrarTitulo();



#endif // COMUN_H_INCLUDED
