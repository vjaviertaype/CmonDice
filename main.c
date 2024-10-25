#include "turno.h"
#include "LIBS/TDA_COLA/cola.h"
#include "LIBS/ARCHIVO/archivo.h"

#define DIFICULTAD_SELECCIONADA 1
#define NOMBRE_CONFIG "config.txt"

void mostrarInstrucciones();
int ingresoDeJugadores(tLista *);
int menuIngresoJugador(tJugador *pj);
void mostrarJugador(tJugador *pj);
int compararEnteros(const void *a, const void *b);

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
    tConfig vec[3];
    tLista jugadores, tabla;
    tJugador jugador_actual;
    int cant_jugadores, i;

    crearLista(&jugadores);
    crearLista(&tabla);
    mostrarInstrucciones();

    cargarConfig(NOMBRE_CONFIG, vec, 3);
    pausa();

    informe = inicializarInforme("informe_loco");

    if ((cant_jugadores = ingresoDeJugadores(&jugadores)) > 0)
    {
        for (i = 1; i <= cant_jugadores; i++)
        {
            sacarPrimeroLista(&jugadores, &jugador_actual, sizeof(tJugador));
            mostrarJugador(&jugador_actual);

            generarCabeceraJugador(informe, i, jugador_actual.nombre_jugador);
            turnoJugador(informe, &jugador_actual, vec[DIFICULTAD_SELECCIONADA]);
            printf("Puntos de %s : %d\n", jugador_actual.nombre_jugador, jugador_actual.puntos);
            fprintf(informe, "Puntaje Final: %d\n", jugador_actual.puntos);
            ponerAlFinal(&jugadores, &jugador_actual, sizeof(tJugador));
        }

        for (i = 0; i < cant_jugadores; i++)
        {
            sacarPrimeroLista(&jugadores, &jugador_actual, sizeof(tJugador));
            insertarOrdenado(&tabla, &jugador_actual, sizeof(tJugador), compararEnteros);
        }
    }
    else
    {
        return ERROR_FATAL;
    }

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
        ponerAlComienzo(l, &jugadorAux, sizeof(tJugador));
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
int compararEnteros(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
}
