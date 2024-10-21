#include "turno.h"

void mostrarInstrucciones();

int main()
{
    /**SIMULACION DE TURNO DE UN JUGADOR*/
    mostrarInstrucciones();

    //Cada jugador arranca con 0 puntos
    tJugador jugador = {"nombre_jugador",0};

    //Configuracion de la partida..inicializacion para pruebas (Se pueden cambiar) :
    // M = dificultad
    // 2 = tiempo que se muestra la secuencia
    // 5 = tiempo que tiene el jugador para responder
    // 3 = cantidad de vidas
    tConfig configuracion = {'M', 2, 5, 3};

    turnoJugador(&jugador, configuracion);

    printf("Puntos de %s : %d\n",jugador.nombre_jugador,jugador.puntos);
    pausa();
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
