#include "turno.h"
#include "LIBS/TDA_COLA/cola.h"
#include "LIBS/ARCHIVO/archivo.h"
#include "LIBS/CONFIG/config.h"
#include "LIBS/SORTEAR_JUG/sortearJugadores.h"
#include "LIBS/MENU/menu.h"

/**
Tareas:
- Crear funcion para selecionar configuracion (@vjaviertaype)
- Crear funciones para generar el informe (@vjaviertaype)
- Mejorar Menus para mas dinamismo (por asignar/revisar en clase)
- Convertir proyecto api en una libreria
- Conversar con el grupo sobre la implementacion de la api
- Crear los casos de prueba (limites)
- Revisar el caso de fin de secuencia (talvez nunca se llegue, (@AlemanMatias)
*/

int main()
{

    CURL *curl;
    inicializa_manejo_curl(&curl);

    menuPrincipal(curl);

    pausa();

    limpia_y_cierra_api(curl);

    return 0;
}
