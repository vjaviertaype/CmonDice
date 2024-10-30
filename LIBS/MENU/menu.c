#include "menu.h"

int menuPrincipal(CURL *curl)
{
    const char *options[] = {"Instrucciones", "Jugar", "Ver dificultades","Desarrolladores", "Salir"};
    int continuar = 1;
    int numOptions = sizeof(options) / sizeof(options[0]);
    int selectedOption;
    tConfig configuraciones[CANT_MAX_CONFIG];

    cargarConfig(NOMBRE_CONFIG, configuraciones, CANT_MAX_CONFIG);

    do
    {
        //limpiarPantalla();
        selectedOption = menuSeleccionable(options,numOptions);

        switch (selectedOption)
        {
        case 0:
            mostrarInstrucciones();
            volverAtras();
            break;
        case 1:
            jugar(curl);
            break;
        case 2:
            verDificultad(configuraciones);
            volverAtras();
            break;
        case 3:
            desarrolladores();
            volverAtras();
            break;
        case 4:
        case ESCAPE:
            puts("Saliendo del juego...\n");
            continuar = 0;
        }

    }
    while(continuar);

    return 0;
}

void mostrarInstrucciones()
{
    mostrarTitulo();
    printf("\033[1;32m"); // Color verde
    puts("Instrucciones:\n");
    printf("\033[0m"); // Restablecer el color

    printf("1. El jugador debe repetir la secuencia de letras que aparece en pantalla.\n");
    printf("2. Solo se puede usar las letras 'A', 'V', 'R', 'N' y 'Z'.\n");
    printf("3. Se debe ingresar un caracter a la vez.\n");
    printf("4. Hay un tiempo limitado para ingresar la secuencia despues de que se muestre.\n");
    printf("5. Una vez ingresada su respuesta, debe esperar a que el tiempo acabe. Si aprieta 'Z', se finaliza el ingreso de respuesta.\n");
    printf("6. Cada ronda aumentara el tiempo para ingresar la secuencia.\n");
    printf("7. Si no contestas, perderas una vida.\n");
    printf("8. Si respondes mal, podras volver atras segun cuantas vidas tengas.\n");
    printf("9. Puedes presionar la tecla 'Z' mientras ingresas la respuesta para usar vidas.\n");
    printf("10. Si te quedas sin vidas, el juego termina.\n");
    printf("\033[1;33m"); // Color amarillo
    printf("\033[0m"); // Restablecer el color
}

int jugar(CURL *curl)
{
    tPila ganadores;
    tLista jugadores, tabla;
    tJugador jugador_actual;
    int cant_jugadores, i, config_seleccionada;
    const char *opciones_config[] = {"FACIL","MEDIO","DIFICIL","SALIR"};

    FILE *informe;
    crearPila(&ganadores);
    crearLista(&jugadores);
    crearLista(&tabla);

    tConfig configuraciones[CANT_MAX_CONFIG];
    cargarConfig(NOMBRE_CONFIG, configuraciones, 3);


    config_seleccionada = seleccionaConfigIndice(opciones_config,CANT_MAX_CONFIG + 1);

    if(config_seleccionada == CANT_MAX_CONFIG) return ERROR;

    informe = inicializarInforme(PREFIJO);


    if ((cant_jugadores = ingresoDeJugadores(&jugadores)) > 0)
    {
        //Se sortea lista dejugadores
        sortearJugadores(&jugadores);
        for (i = 1; i <= cant_jugadores; i++)
        {
            sacarPrimeroLista(&jugadores, &jugador_actual, sizeof(tJugador));
            mostrarTurnoJugador(&jugador_actual);

            generarCabeceraJugador(informe, i, jugador_actual.nombre_jugador);
            turnoJugador(informe, &jugador_actual, configuraciones[config_seleccionada], curl, URL);

            printf("Puntos de %s : %d\n\n", jugador_actual.nombre_jugador, jugador_actual.puntos);

            fprintf(informe, "Puntaje Final: %d\n", jugador_actual.puntos);
            pausa();
            insertarOrdenado(&tabla, &jugador_actual, sizeof(tJugador), compararPuntajeJugador, true, false);

            cargarPilaGanadores(&ganadores, &jugador_actual, compararPuntajeJugador);
        }
        mostrarGanadores(&ganadores);
        pausa();
        finalizarInforme(informe, &tabla, compararEnteros);
    }

    vaciarPila(&ganadores);
    vaciarLista(&jugadores);
    vaciarLista(&tabla);

    return TODO_OK;
}

void mostrarJugador(void *e)
{
    tJugador *j = e;

    printf("%s - %d\n",j->nombre_jugador,j->puntos);
}

int ingresoDeJugadores(tLista *l)
{
    tJugador jugadorAux;
    int cant_jugadores = 0;

    while (menuIngresoJugador(&jugadorAux,cant_jugadores) == TODO_OK)
    {
        ponerAlFinal(l, &jugadorAux, sizeof(tJugador));
        cant_jugadores++;
    }

    return cant_jugadores;
}

int menuIngresoJugador(tJugador *pj,int num_jugador)
{
    const char *titulo = "INGRESE NOMBRE DEL JUGADOR (0 PARA FINALIZAR INGRESO)\n\n";
    int espacio_separacion = 10; // Ajusta el espaciado según sea necesario

    mostrarTitulo();
    printf("\033[1;34m"); // Color azul y negrita
    printf("%*s%s%*s\n", espacio_separacion, "", titulo, espacio_separacion, "");
    printf("\033[1;31m"); // Rojo y negrita
    printf("Jugador numero %d: ",num_jugador + 1);
    printf("\033[0m"); // Restablecer el color
    limpiarBufferTeclado();
    scanf("%s", pj->nombre_jugador);
    pj->puntos = 0;

    if (strcmp(pj->nombre_jugador, "0") == 0)
    {
        return EXIT;
    }

    return TODO_OK;
}

void mostrarTurnoJugador(tJugador *pj)
{
    mostrarTitulo();
    printf("\033[1;34m");

    puts("Turno del jugador: ");
    printf("\033[0m"); // Restablecer el color
    printf("%-17s\n\n", pj->nombre_jugador);
    printf("\033[1;34m");
    puts("");

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



void desarrolladores()
{
    mostrarTitulo();
    printf("\033[1;32m"); // Verde y en negrita
    puts("Juego desarrollado para la materia Algoritmos Y Etructuras de Datos de la Universidad Nacional de La Matanza");
    printf("\033[0m"); // Blanco normal
    puts("\nDesarrolladores:");
    puts("Gonzalo Mendoza");
    puts("Victor Javier Taype");
    puts("Matias Aleman Flores");
    puts("Lucas Tomas Perez");
    puts("Thomas Delli Gatti");
    puts("Victor Beltramino");
    puts("\nDocentes:");
    puts("Renata Guatelli");
    puts("Giselle Rocio Gonzalez");
}

void verDificultad(tConfig *vec)
{
    mostrarTitulo();
    mostrarConfig(vec);
}

void volverAtras()
{
    int key;
    printf("\n\n> Volver Atras");
    do
    {
        key = _getch();
    }
    while(key != '\r');
}

