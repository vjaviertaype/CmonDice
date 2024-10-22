#include "turno.h"
#include "LIBS/TDA_COLA/cola.h"

#define DIFICULTAD_SELECCIONADA 1

void mostrarInstrucciones();
int ingresoDeJugadores(tCola *);
int menuIngresoJugador(tJugador *pj);
void mostrarJugador(tJugador pj);

/**
Tareas:
- Crear funcion para seleecionar configuracion (@vjaviertaype)
- Crear funciones para generar el informe (@vjaviertaype)
- Mejorar Menus para mas dinamismo (por asignar/revisar en clase)
- Convertir proyecto api en una libreria
- Conversar con el grupo sobre la implementacion de la api
- Crear los casos de prueba (limites)
- Revisar el caso de fin de secuencia (talvez nunca se llegue, (@AlemanMatias)
*/

int main()
{
    tCola jugadores;
    tJugador jugador_actual;
    tConfig vec[3];
    int cant_jugadores;

    crearCola(&jugadores);
    mostrarInstrucciones();

    cargarConfig("config.txt",vec,3);
    pausa();


    /**SIMULACION DE TURNO DE UN JUGADOR*/
    if((cant_jugadores = ingresoDeJugadores(&jugadores)) != 0)
    {
        for(int i = 0; i < cant_jugadores; i++)
        {
            sacarDeCola(&jugadores,&jugador_actual,sizeof(tJugador));
            mostrarJugador(jugador_actual);
            turnoJugador(&jugador_actual,vec[DIFICULTAD_SELECCIONADA]);
            printf("Puntos de %s : %d\n",jugador_actual.nombre_jugador,jugador_actual.puntos);
            ponerEnCola(&jugadores,&jugador_actual,sizeof(tJugador));
        }
    }
    else
    {
        return ERROR_FATAL;
    }


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

int ingresoDeJugadores(tCola *c)
{
    tJugador jugadorAux;
    int cant_jugadores = 0;

    while(menuIngresoJugador(&jugadorAux) == TODO_OK)
    {
        ponerEnCola(c,&jugadorAux,sizeof(tJugador));
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
    scanf("%s",pj->nombre_jugador);
    pj->puntos = 0;

    if(strcmp(pj->nombre_jugador,"0") == 0)
    {
        return EXIT;
    }

    printf("\nPresiona Enter para continuar...\n");
    getchar();

    return TODO_OK;
}

void mostrarJugador(tJugador pj) {
    limpiarPantalla();
    printf("*****************************\n");
    printf("***** %-17s *****\n",pj.nombre_jugador);
    printf("*****************************\n");
    pausa();
}
