#ifndef COMUN_H_INCLUDED
#define COMUN_H_INCLUDED

#include <time.h>

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
void colorearCaracterVerde(char c);
void colorearCaracterNaranja(char c);
void colorearCaracterAmarillo(char c);
void colorearCaracterRojo(char c);

#endif // COMUN_H_INCLUDED
