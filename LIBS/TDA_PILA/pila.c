/*** PILA-DINAMICA-.C ***/
#include "pila.h"

void crearPila(tPila* p)
{
    *p = NULL;
}

int pilaLLena(const tPila* p, unsigned cantBytes)
{
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    void *info = malloc(cantBytes);

    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}

int ponerEnPila(tPila* p, const void* dato, unsigned cantBytes)
{

    tNodo* nue;

    if((nue = (tNodo* )malloc(sizeof(tNodo))) == NULL  || (nue->info = malloc(cantBytes))== NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, dato, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = *p;
    *p = nue;

    return 1;
}

int verTope(const tPila* p, void* dato, unsigned cantBytes)
{
    if(*p == NULL)
        return 0;
    memcpy(dato, (*p)->info, minimo(cantBytes, (*p)->tamInfo));

    return 1;
}

int pilaVacia(const tPila* p)
{
    return *p == NULL;
}

int sacarDePila(tPila* p, void* dato, unsigned cantBytes)
{
    tNodo* aux = *p;

    if(aux == NULL)
        return 0;
    *p = aux->sig;
    memcpy(dato, aux->info, minimo(cantBytes, aux->tamInfo));
    free(aux->info);
    free(aux);

    return 1;
}

void vaciarPila(tPila* p)
{
    while(*p)
    {
        tNodo* aux = *p;

        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
}

///*** PILA-ESTATICA-.C***/
//
//#include "pila.h"
//
//void crearPila(tPila* p)
//{
//    p->tope = TAM_PILA;//
//}
//
//int pilaLLena(const tPila* p, unsigned cantBytes)
//{
//    return p->tope < cantBytes  + sizeof(unsigned);
//}
//
//int ponerEnPila(tPila* p, const void* dato, unsigned cantBytes)
//{
//    if(p->tope < cantBytes + sizeof(unsigned))
//        return 0;
//    p->tope -= cantBytes;
//    memcpy(p->pila + p->tope, dato, cantBytes);
//    p->tope -= sizeof(unsigned);
//    memcpy(p->pila + p->tope, &cantBytes, sizeof(unsigned));
//    return 1;
//}
//
//int verTope(const tPila* p, void* dato, unsigned cantBytes)
//{
//    unsigned tamInfo;
//    if(p->tope == TAM_PILA)
//        return 0;
//    memcpy(&tamInfo, p->pila + p->tope, sizeof(unsigned));
//    memcpy(dato, p->pila + p->tope + sizeof(unsigned), minimo(tamInfo, cantBytes));
//
//    return 1;
//}
//
//int pilaVacia(const tPila* p)
//{
//    return p->tope == TAM_PILA;
//}
//
//int sacarDePila(tPila* p, void* dato, unsigned cantBytes)
//{
//    unsigned tamInfo;
//    if(p->tope == TAM_PILA)
//        return 0;
//    memcpy(&tamInfo, p->pila + p->tope, sizeof(unsigned));
//    p->tope += sizeof(unsigned);
//    memcpy(dato, p->pila + p->tope, minimo(tamInfo, cantBytes));
//    p->tope += tamInfo;
//    return 1;
//}
//
//void vaciarPila(tPila* p)
//{
//    p->tope = TAM_PILA;
//}


