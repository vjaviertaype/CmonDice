#ifndef COMUN_H_INCLUDED
#define COMUN_H_INCLUDED

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

#endif // COMUN_H_INCLUDED
