#include "turno.h"
#include "LIBS/TDA_COLA/cola.h"
#include "LIBS/ARCHIVO/archivo.h"
#include "LIBS/SORTEAR_JUG/sortearJugadores.h"
#include "LIBS/MENU/menu.h"

int main()
{

    CURL *curl;

    inicializa_manejo_curl(&curl);

    menuPrincipal(curl);

    limpia_y_cierra_api(curl);

    return 0;
}



