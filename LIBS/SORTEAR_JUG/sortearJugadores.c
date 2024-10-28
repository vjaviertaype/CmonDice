#include "sortearJugadores.h"


tNodo* obtenerNodoEnIndice(tLista *lista, int indice)
{
    tNodo *actual = *lista;
    for (int i = 0; i < indice && actual != NULL; i++)
    {
        actual = actual->sig;
    }
    return actual;
}


int sortearJugadores(tLista *lista)
{
    int totalNodos = contarNodos(lista);
    int i, indiceAleatorio;
    tNodo *actual, *nodoAleatorio;
    void *temp;

    if (totalNodos < 2) return 1;

    actual = *lista;
    temp = malloc(actual->tamInfo);
    if (!temp) return 0;

    for (i = 0; i < totalNodos - 1; i++)
    {
        indiceAleatorio = i + rand() % (totalNodos - i);
        nodoAleatorio = obtenerNodoEnIndice(lista, indiceAleatorio);

        memcpy(temp, actual->info, actual->tamInfo);
        memcpy(actual->info, nodoAleatorio->info, actual->tamInfo);
        memcpy(nodoAleatorio->info, temp, actual->tamInfo);

        actual = actual->sig;
    }

    free(temp);
    return 1;
}
