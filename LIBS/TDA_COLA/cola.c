/***COLA-DINAMICA-.C ***/

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


///***COLA-ESTATICA-.C ***/
//
//#include"cola.h"
//
//void crearCola(tCola *cola)
//{
//    cola->pri = TAM_COLA - 70;
//    cola->ult = TAM_COLA - 70;
//    cola->tamDisp = TAM_COLA;
//}
//
//int colaLena(const tCola *cola, unsigned cantBytes)
//{
//    return cola->tamDisp < cantBytes + sizeof(unsigned);
//}
//
//int ponerEnCola(tCola *cola, const void *dato, unsigned cantBytes)
//{
//    unsigned ini, fin;
//
//    if(cola->tamDisp < sizeof(unsigned) + cantBytes)
//        return 0;
//    cola->tamDisp -= sizeof(unsigned) + cantBytes;
//
//    if((ini = minimo(sizeof(cantBytes), TAM_COLA - cola->ult)) != 0)
//        memcpy(cola->cola + cola->ult, &cantBytes, ini);
//    if((fin = sizeof(cantBytes) - ini) != 0)
//        memcpy(cola->cola, ((char*)&cantBytes) + ini, fin);
//    cola->ult = fin? fin : cola->ult + ini;
//
//    if((ini = minimo(cantBytes, TAM_COLA - cola->ult)) != 0)
//        memcpy(cola->cola + cola->ult, dato, ini);
//    if((fin = cantBytes - ini) != 0)
//        memcpy(cola->cola, ((char*)dato) + ini, fin);
//
//    cola->ult = fin? fin : cola->ult + ini;
//
//    return 1;
//}
//
//void vaciarCola(tCola *cola)
//{
//    cola->ult = cola->pri;
//    cola->tamDisp = TAM_COLA;
//}
//
//int colaVacia(const tCola *cola)
//{
//    return cola->tamDisp == TAM_COLA;
//}
//
//
//int sacarDeCola(tCola *cola, void *dato, unsigned cantBytes)
//{
//    unsigned tamInfo, ini, fin;
//
//    if(cola->tamDisp == TAM_COLA)
//        return 0;
//
//    if((ini = minimo(sizeof(unsigned), TAM_COLA - cola->pri)) != 0)
//        memcpy(&tamInfo, cola->cola + cola->pri, ini);
//    if((fin = sizeof(unsigned) - ini) != 0)
//        memcpy(((char*)&tamInfo) + ini, cola->cola, fin);
//
//    cola->pri = fin? fin : cola->pri + ini;
//
//    cola->tamDisp += sizeof(unsigned) + tamInfo;
//
//    tamInfo = minimo(tamInfo, cantBytes);
//
//    if((ini = minimo(tamInfo, TAM_COLA - cola->pri)) != 0)
//        memcpy(dato, cola->cola + cola->pri, ini);
//    if((fin = tamInfo - ini) != 0)
//        memcpy(((char*)dato) + ini, cola->cola, fin);
//
//    cola->pri = fin? fin : cola->pri + ini;
//
//    return 1;
//}
