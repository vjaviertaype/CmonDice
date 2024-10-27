#include "turno.h"
#include "LIBS/TDA_COLA/cola.h"
#include "LIBS/ARCHIVO/archivo.h"
#include "LIBS/CONFIG/config.h"
#include "LIBS/SORTEAR_JUG/sortearJugadores.h"

#define CANT_MAX_CONFIG 3
#define NOMBRE_CONFIG "config.txt"

void mostrarInstrucciones();
int ingresoDeJugadores(tLista *);
int menuIngresoJugador(tJugador *pj);
void mostrarJugador(tJugador *pj);
int compararEnteros(const void *a, const void *b);

int compararPuntajeJugador(const void *a, const void *b);

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
    FILE *informe;
    tConfig vec[CANT_MAX_CONFIG];
    tLista jugadores, tabla;
    tJugador jugador_actual;
    int cant_jugadores, i,config_seleccionada;

    ///Integracion de libreria API
    CURL *curl;
    const char * url = "https://www.random.org/integers/?num=1&min=1&max=4&col=1&base=10&format=plain&rnd=new";
    inicializa_manejo_curl(&curl);

    crearLista(&jugadores);
    crearLista(&tabla);

    mostrarInstrucciones();
    cargarConfig(NOMBRE_CONFIG, vec, CANT_MAX_CONFIG);

    config_seleccionada = seleccionaConfigIndice(vec,CANT_MAX_CONFIG);

    mostrarConfig(config_seleccionada,vec + config_seleccionada);
    pausa();

    informe = inicializarInforme("informe_loco");



    if ((cant_jugadores = ingresoDeJugadores(&jugadores)) > 0)
    {
        //Se sortea lista dejugadores
        sortearJugadores(&jugadores);
        for (i = 1; i <= cant_jugadores; i++)
        {
            sacarPrimeroLista(&jugadores, &jugador_actual, sizeof(tJugador));
            mostrarJugador(&jugador_actual);

            generarCabeceraJugador(informe, i, jugador_actual.nombre_jugador);
            turnoJugador(informe, &jugador_actual, vec[config_seleccionada], curl, url);
            printf("Puntos de %s : %d\n", jugador_actual.nombre_jugador, jugador_actual.puntos);
            fprintf(informe, "Puntaje Final: %d\n", jugador_actual.puntos);

            pausa();
            insertarOrdenado(&tabla, &jugador_actual, sizeof(tJugador), compararPuntajeJugador, true, false);
        }
    }
    else
    {
        return ERROR_FATAL;
    }
    limpia_y_cierra_api(curl);
    finalizarInforme(informe, &tabla, compararEnteros);
    return 0;
}

void mostrarInstrucciones()
{
    limpiarPantalla();
    printf("******************************\n");
    printf("***** SIMULACION DE JUEGO ****\n");
    printf("******************************\n");
    printf("1. El jugador debe repetir la secuencia de letras que le aprezca en pantalla.\n");
    printf("2. Solo se puede usar las letras 'A', 'V', 'R', 'N' y 'Z'.\n");
    printf("3. Se debe ingresar un caracter a la vez.\n");
    printf("4. Hay un tiempo limitado para ingresar la secuencia despues de que se muestre.\n");
    printf("5. Una vez ingresada su respuesta, debe esperar a que el tiempo acabe. Si apreto Z se finaliza el ingreso de respuesta.\n");
    printf("6. Cada ronda aumentara el tiempo para ingresar la secuencia.\n");
    printf("7. Si no contestas, perderas una vida.\n");
    printf("8. Si respondes mal podras volver atras segun cuantas vidas tengas\n");
    printf("9. Puedes presionar la tecla 'Z' mientras ingresas la respuesta para usar vidas.\n");
    printf("10. Si te quedas sin vidas, el juego termina.\n");

    printf("\nPresiona Enter para comenzar...\n");
    getchar();
}

int ingresoDeJugadores(tLista *l)
{
    tJugador jugadorAux;
    int cant_jugadores = 0;

    while (menuIngresoJugador(&jugadorAux) == TODO_OK)
    {
        ponerAlFinal(l, &jugadorAux, sizeof(tJugador));
        cant_jugadores++;
    }

    return cant_jugadores;
}

int menuIngresoJugador(tJugador *pj)
{
    limpiarPantalla();
    printf("*****************************\n");
    printf("***** INGRESE UN NOMBRE *****\n");
    printf("*****************************\n");
    printf("\"Ingrese \'0\' para finalizar el ingreso de jugadores\"\n");
    printf("-> ");
    scanf("%s", pj->nombre_jugador);
    pj->puntos = 0;

    if (strcmp(pj->nombre_jugador, "0") == 0)
    {
        return EXIT;
    }

    return TODO_OK;
}

void mostrarJugador(tJugador *pj)
{
    limpiarPantalla();
    printf("*****************************\n");
    printf("***** Turno de %-17s *****\n", pj->nombre_jugador);
    printf("*****************************\n");
    pausa();
}

int compararPuntajeJugador(const void *a, const void *b)
{
    tJugador* e1 = (tJugador* )a;
    tJugador* e2 = (tJugador* )b;

    return e1->puntos - e2->puntos;
}

int compararEnteros(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
}
