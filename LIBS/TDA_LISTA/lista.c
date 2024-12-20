#include "lista.h"

void crearLista(tLista* l)
{
    *l = NULL;
}

int listaVacia(const tLista* l)
{
    return *l == NULL;
}

int listaLLena(const tLista* l, unsigned cantBytes)
{
    tNodo* aux = (tNodo* )malloc(sizeof(tNodo));
    void* info = malloc(cantBytes);

    free(aux);
    free(info);

    return aux == NULL || info == NULL;
}

void vaciarLista(tLista* l)
{
    while(*l)
    {
        tNodo* aux = *l;

        *l = aux->sig;
        free(aux->info);
        free(aux);
    }
}

int ponerAlComienzo(tLista* l, const void* dato, unsigned cantBytes)
{
    tNodo* nue;

    if((nue = (tNodo* )malloc(sizeof(tNodo))) == NULL  ||
            (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, dato, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = *l;
    *l = nue;

    return 1;
}

int sacarPrimeroLista(tLista* l, void* dato, unsigned cantBytes)
{
    tNodo* aux = *l;

    if(aux == NULL)
        return 0;

    *l = aux->sig;
    memcpy(dato, aux->info, minimo(cantBytes, aux->tamInfo));
    free(aux->info);
    free(aux);

    return 1;
}

int verPrimeroLista(const tLista* l, void* dato, unsigned cantBytes)
{
    if(*l == NULL)
        return 0;

    memcpy(dato, (*l)->info, minimo(cantBytes, (*l)->tamInfo));

    return 1;
}

int ponerAlFinal(tLista* l, const void* dato, unsigned cantBytes)
{
    tNodo* nue;

    while(*l)
        l = &(*l)->sig;

    if((nue = (tNodo* )malloc(sizeof(tNodo))) == NULL  ||
            (nue->info = malloc(cantBytes)) == NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, dato, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = NULL;
    *l = nue;

    return 1;
}

int sacarUltimoLista(tLista* l, void* dato, unsigned cantBytes)
{
    if(*l == NULL)
        return 0;

    while((*l)->sig)
        l = &(*l)->sig;
    memcpy(dato, (*l)->info, minimo(cantBytes, (*l)->tamInfo));
    free((*l)->info);
    free(*l);
    *l = NULL;

    return 1;
}

int verUltimoLista(const tLista* l, void* dato, unsigned cantBytes)
{
    if(*l == NULL)
        return 0;

    while((*l)->sig)
        l = &(*l)->sig;

    memcpy(dato, (*l)->info, minimo(cantBytes, (*l)->tamInfo));

    return 1;
}

void mapLista(tLista* l, void* contexto, Accion accion)
{
    while(*l)
    {
        accion((*l)->info, contexto);
        l = &(*l)->sig;
    }
}

int eliminarNUltimos(tLista* l, unsigned cantBytes, int cantElim)
{
    if (!*l)
    {
        return 0; // Lista vacía
    }

    if (cantElim <= 0)
    {
        return 0; // No se eliminarán elementos si el número es menor o igual a 0
    }

    int eliminados = 0;

    void* info = malloc(cantBytes);
    if(!info)
        return 0;

    // Elimina hasta cantElim elementos o hasta que la lista quede vacía
    while (sacarUltimoLista(l, info, cantBytes) && ++eliminados < cantElim);

    free(info);
    return 0;
}

int mostrarSecuencia(tLista* l, Mostrar mostrar)
{
    tNodo** nodo_actual = l;

    while (*nodo_actual)
    {
        mostrar((*nodo_actual)->info);
        nodo_actual = &(*nodo_actual)->sig;
        Sleep(300);
    }

    return 1;
}

//Retorna un 1 si las listas son iguales
int listasIguales(tLista* l_uno,tLista* l_dos,Cmp cmp)
{
    tNodo** e1 = l_uno;
    tNodo** e2 = l_dos;

    while( *e1 && *e2 )
    {
        if( cmp((*e1)->info, (*e2)->info) != 0 )
            return 0;

        e1 = &(*e1)->sig;
        e2 = &(*e2)->sig;
    }

    //Para que sean iguales ambos nodos deben contener null
    if( *e1 || *e2 )
        return 0;

    return 1;
}

int insertarOrdenado(tLista* l, void* dato, unsigned cantBytes, Cmp cmp, bool duplicado, bool ordenAsc)
{
    while (*l && (ordenAsc ? cmp(dato, (*l)->info) > 0 : cmp(dato, (*l)->info) < 0))
    {
        l = &(*l)->sig;
    }

    if (*l != NULL && cmp((*l)->info, dato) == 0 && !duplicado)
        return 0;

    tNodo* nue = malloc(sizeof(tNodo));
    if (!nue)
        return 0;

    nue->info = malloc(cantBytes);
    if (!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, dato, cantBytes);
    nue->tamInfo = cantBytes;

    nue->sig = *l;
    *l = nue;

    return 1;
}

int contarNodos(tLista *lista)
{
    int cont = 0;
    tNodo *actual = *lista;
    while (actual)
    {
        cont++;
        actual = actual->sig;
    }
    return cont;
}
