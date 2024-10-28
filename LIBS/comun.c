#include "comun.h"
#include "TDA_LISTA/lista.h"

void obtenerFechaDeAhora(char *buffer, unsigned tam)
{
    time_t tiempoActual = time(NULL);
    struct tm *infoTiempo = localtime(&tiempoActual);

    strftime(buffer, tam, "%Y-%m-%d-%H-%M", infoTiempo);
}
