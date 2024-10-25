#include "cola.h"

void crearCola(tCola *cola)
{
    cola->pri = NULL;
    cola->ult = NULL;
}

int colaLena(const tCola *cola, unsigned cantBytes)
{
    tNodo *aux = (tNodo *)malloc(sizeof(tNodo));
    void *info = malloc(cantBytes);

    free(aux);
    free(info);

    return aux == NULL || info == NULL;
}

int ponerEnCola(tCola *cola, const void *dato, unsigned cantBytes)
{
    tNodo *nue = (tNodo *)malloc(sizeof(tNodo));

    if(nue == NULL  || (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, dato, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;

    if(cola->ult)
        cola->ult->sig = nue;
    else
        cola->pri = nue;

    cola->ult = nue;

    return 1;
}

void vaciarCola(tCola *cola)
{
    while(cola->pri)
    {
        tNodo *aux = cola->pri;
        cola->pri = aux->sig;
        free(aux->info);
        free(aux);
    }
    cola->ult = NULL;
}

int colaVacia(const tCola *cola)
{
    return cola->pri == NULL;
}

int sacarDeCola(tCola *cola, void *dato, unsigned cantBytes)
{
    tNodo *aux = cola->pri;
    if(aux == NULL)
        return 0;

    cola->pri = aux->sig;

    memcpy(dato, aux->info, minimo(cantBytes, aux->tamInfo));

    free(aux->info);
    free(aux);

    if(cola->pri == NULL)
        cola->ult = NULL;

    return 1;
}


int verPrimeroCola(const tCola *cola, void *dato, unsigned cantBytes)
{
    tNodo *aux = cola->pri;
    if(aux == NULL)
        return 0;

    memcpy(dato, aux->info, minimo(cantBytes, aux->tamInfo));

    return 1;
}
