#include "menu.h"
int menuPrincipal(CURL *curl)
{
    tConfig configuraciones[CANT_MAX_CONFIG];
    cargarConfig(NOMBRE_CONFIG, configuraciones, 3);
    const char *options[] = {"Instrucciones", "Jugar", "Ver dificultades","Desarrolladores", "Salir"};
    int numOptions = sizeof(options) / sizeof(options[0]);
    int selectedOption;

    limpiarPantalla();
    selectedOption = menuSeleccionable(options,numOptions);

     switch (selectedOption)
        {
        case 0:
            mostrarInstrucciones(curl);
            volverAtras(curl);
            break;
        case 1:
            jugar(curl);
            break;
        case 2:
            verDificultad(curl,configuraciones);
            volverAtras(curl);
            break;
        case 3:
            desarrolladores(curl);
            break;
        case ESCAPE:
            puts("Saliendo del juego...\n");
            pausa();
        }


    return 0;
}

int menuSeleccionable(const char *options[], int numOptions){

  int key;
 int selectedOption = 0;
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

    } while(key != '\r' && key != ESCAPE);

    if (key == ESCAPE) return ESCAPE;
    return selectedOption;
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

    volverAtras(curl);
}

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls"); // Limpia la pantalla en Windows
#else
    system("clear"); // Limpia la pantalla en Linux
#endif
}

int jugar(CURL *curl)
{

    tLista jugadores, tabla;
    tJugador jugador_actual;
<<<<<<< Updated upstream
    int cant_jugadores, i;
    tConfig vec[3];
    FILE *informe;
    crearLista(&jugadores);
    crearLista(&tabla);
    cargarConfig(NOMBRE_CONFIG, vec, 3);
=======
    int cant_jugadores, i, config_seleccionada;
    FILE *informe;
    crearLista(&jugadores);
    crearLista(&tabla);
    const char *options[] = {"Volver al menu principal","Salir del juego"};
    int numOptions = sizeof(options) / sizeof(options[0]);
    int selectedOption;

    tConfig configuraciones[CANT_MAX_CONFIG];
    cargarConfig(NOMBRE_CONFIG, configuraciones, 3);


    config_seleccionada = seleccionaConfigIndice(configuraciones);

>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
            turnoJugador(informe, &jugador_actual, vec[DIFICULTAD_SELECCIONADA], curl, URL);
            printf("Puntos de %s : %d\n", jugador_actual.nombre_jugador, jugador_actual.puntos);
=======
            turnoJugador(informe, &jugador_actual, configuraciones[config_seleccionada], curl, URL);
            printf("Puntos de %s : %d\n\n", jugador_actual.nombre_jugador, jugador_actual.puntos);
>>>>>>> Stashed changes
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

    vaciarLista(&jugadores);
    vaciarLista(&tabla);

    selectedOption = menuSeleccionable(options,numOptions);

    if (selectedOption == 0){
    menuPrincipal(curl);
    }

    return 1;
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
    int espacioIzquierdo = 10; // Ajusta el espaciado según sea necesario
    limpiarPantalla();
    printf("\033[1;34m"); // Color azul y negrita
    printf("%*s%s%*s\n", espacioIzquierdo, "", titulo, espacioIzquierdo, "");
    printf("\033[1;31m"); // Rojo y negrita
    printf("Jugador numero %d: ",num_jugador +1);
    printf("\033[0m"); // Restablecer el color
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
    limpiarPantalla();
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
    limpiarPantalla();

    printf("\033[1;32m"); // Verde y en negrita
    puts("Juego desarrollado para la materia Algoritmos Y Etructuras de Datos de la Universidad Nacional de La Matanza");
    printf("\033[0;37m"); // Blanco normal
    puts("\nDesarrolladores:");
    puts("Gonzalo Mendoza");
    puts("Victor Javier Taype");
    puts("Matias Aleman Flores");
    puts("Lucas Tomas Perez");
    puts("Thomas Delli Gatti");
    puts("Victor Beltramino");
    puts("\nDocentes:");
    puts("Renata Guatelli:");
    puts("Giselle Rocio Gonzalez:\n");

    volverAtras(curl);
}

void verDificultad(CURL*curl,tConfig *vec)
{
    limpiarPantalla();
    puts("Las dificultades del juego son: \n\n");
    mostrarConfig(vec);
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
