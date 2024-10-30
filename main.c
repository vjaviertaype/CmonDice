#include "turno.h"
#include "LIBS/ARCHIVO/archivo.h"
#include "LIBS/CONFIG/config.h"
#include "LIBS/SORTEAR_JUG/sortearJugadores.h"
#include "LIBS/MUSICA/musica.h"
#include "LIBS/MENU/menu.h"

int main()
{
    CURL *curl;

    ocultarCursor();

    inicializa_manejo_curl(&curl);

    reproducir_musica(SONG_NAME);

    mostrarArteASCII(SPLASH_ART);
    getchar();

    menuPrincipal(curl);

    limpia_y_cierra_api(curl);

    mostrarCursor();

    return 0;
}
