#include "menu.h"

int menuPrincipal(CURL *curl)
{
    limpiarPantalla();
    const char *options[] = {"Instrucciones", "Jugar", "Ver dificultades","Desarrolladores", "Salir"};

    int numOptions = sizeof(options) / sizeof(options[0]);

    int selectedOption = 0;
    int key;

    do
    {
        displayMenu(options, numOptions, selectedOption);
        key = _getch(); // Captura la tecla

        if (key == 0 || key == 224)
        {
            key = _getch(); // Captura las teclas especiales
            if (key == UP_ARROW && selectedOption > 0)
            {
                selectedOption--;
            }
            else if (key == DOWN_ARROW && selectedOption < numOptions - 1)
            {
                selectedOption++;
            }
        }
        else if (key == '\r')     // Captura Enter
        {
            break; // Sale del bucle al presionar Enter
        }
    }
    while (key != ESCAPE);   // Sale cuando se presiona Escape

    if (key == ESCAPE)
    {
        printf("\nSaliendo del juego...\n");
    }
    else
    {
        switch (selectedOption)
        {
        case 0:
            mostrarInstrucciones(curl);
            volverAtras(curl);
            break;
        case 1:
            // elegirDificultad();
            jugar(curl);
            break;
        case 2:
            verDificultad(curl);
            volverAtras(curl);
            break;
        case 3:
            desarrolladores(curl);

            break;
        case 4:
            printf("Saliendo del juego...\n");
            break;
        }
    }

    system("pause");
    return 0;
}


void gotoxy(int x, int y)
{
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void displayMenu(const char *options[], int numOptions, int selectedOption)
{
    limpiarPantalla();
    mostrarTitulo();
    printf("=== Menu de Opciones === (Seleccione con enter)\n\n");

    for (int i = 0; i < numOptions; i++)
    {
        if (i == selectedOption)
        {
            printf(" > %s\n", options[i]); // Opción seleccionada
        }
        else
        {
            printf("   %s\n", options[i]);
        }
    }
}

void mostrarInstrucciones(CURL*curl)
{
    limpiarPantalla();

    mostrarTitulo();

    printf("\033[1;32m"); // Color verde
    puts("Instrucciones:\n");
    printf("\033[0m"); // Restablecer el color

    printf("1. El jugador debe repetir la secuencia de letras que aparece en pantalla.\n");
    printf("2. Solo se puede usar las letras 'A', 'V', 'R', 'N' y 'Z'.\n");
    printf("3. Se debe ingresar un carácter a la vez.\n");
    printf("4. Hay un tiempo limitado para ingresar la secuencia después de que se muestre.\n");
    printf("5. Una vez ingresada su respuesta, debe esperar a que el tiempo acabe. Si aprieta 'Z', se finaliza el ingreso de respuesta.\n");
    printf("6. Cada ronda aumentará el tiempo para ingresar la secuencia.\n");
    printf("7. Si no contestas, perderás una vida.\n");
    printf("8. Si respondes mal, podrás volver atrás según cuántas vidas tengas.\n");
    printf("9. Puedes presionar la tecla 'Z' mientras ingresas la respuesta para usar vidas.\n");
    printf("10. Si te quedas sin vidas, el juego termina.\n");
    printf("\033[1;33m"); // Color amarillo
    printf("\033[0m"); // Restablecer el color

    volverAtras(curl);
}

int jugar(CURL *curl)
{

    tLista jugadores, tabla;
    tJugador jugador_actual;
    int cant_jugadores, i, config_seleccionada;
    tConfig configuraciones[CANT_MAX_CONFIG];
    FILE *informe;
    crearLista(&jugadores);
    crearLista(&tabla);

    cargarConfig(NOMBRE_CONFIG, configuraciones, 3);

    config_seleccionada = seleccionaConfigIndice(configuraciones,CANT_MAX_CONFIG);

    informe = inicializarInforme("informe_loco");


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


    finalizarInforme(informe, &tabla, compararEnteros);
    return 1;
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
    static int cant_jugadores_turno = 1;
    const char *titulo = "INGRESE NOMBRE DEL JUGADOR (0 PARA FINALIZAR INGRESO)\n\n";
    int espacioIzquierdo = 10; // Ajusta el espaciado según sea necesario
    limpiarPantalla();
    printf("\033[1;34m"); // Color azul y negrita
    printf("%*s%s%*s\n", espacioIzquierdo, "", titulo, espacioIzquierdo, "");
    printf("\033[1;31m"); // Rojo y negrita
    printf("Jugador numero %d: ",cant_jugadores_turno);
    printf("\033[0m"); // Restablecer el color
    scanf("%s", pj->nombre_jugador);
    pj->puntos = 0;
    cant_jugadores_turno++;
    if (strcmp(pj->nombre_jugador, "0") == 0)
    {
        return EXIT;
    }

    return TODO_OK;
}

void mostrarTurnoJugador(tJugador *pj)
{
    limpiarPantalla();
    printf("\033[1;34m");
    mostrarTitulo();

    puts("Turno del jugador: ");
    printf("\033[0m"); // Restablecer el color
    printf("%-17s", pj->nombre_jugador);
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

void mostrarTitulo()
{
    const char *titulo = "CMON DICE";
    int anchoConsola = 100; // Ajusta según necesites
    int longitudTitulo = strlen(titulo);
    int espacioIzquierdo = (anchoConsola - longitudTitulo) / 2;

    printf("\033[1;34m"); // Color azul y negrita
    printf("%*s%s%*s\n", espacioIzquierdo, "", titulo, espacioIzquierdo, "");
    printf("***************************************************************************************************\n\n");
    printf("\033[0m"); // Restablecer el color

}

void desarrolladores(CURL*curl)
{
    puts("los desarrolladores son");

    volverAtras(curl);
}

void verDificultad(CURL*curl)
{
    puts("la dificultad es");
    volverAtras(curl);
}

void volverAtras(CURL* curl)
{
    int key;
    printf("\n\n> Volver Atras");
    do
    {
        key = _getch();
    }
    while(key != '\r');
    menuPrincipal(curl);
}
