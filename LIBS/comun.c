#include "comun.h"
#include "TDA_LISTA/lista.h"

void obtenerFechaDeAhora(char *buffer, unsigned tam)
{
    time_t tiempoActual = time(NULL);
    struct tm *infoTiempo = localtime(&tiempoActual);

    strftime(buffer, tam, "%Y-%m-%d-%H-%M", infoTiempo);
}

///Funcion que limpia el buffer de teclado en su totalidad...
void limpiarBufferTeclado()
{
    fflush(stdin);
    /**fflush solo limpia el buffer de teclado hasta encontrar un salto de linea (\n), Eso significa que
        ... cualquier cosa después del primer "\n" permanecerá en el buffer.
        Ejemplo : si el usuario escribio por teclado : "xrty\n\n\nrb\n"
        fflush(stdin) solo borrara "xrty\n", pero en el buffer de teclado seguira quedando "\n\nrb\n"

    Para solucionar esto :
        La librería windows.h proporciona funciones específicas para la interacción con el sistema operativo Windows.
        En este caso, utilizamos GetStdHandle para obtener el "handle" o manejador del buffer de entrada de la consola (STD_INPUT_HANDLE)
        ... y FlushConsoleInputBuffer para limpiar dicho buffer, eliminando cualquier entrada PENDIENTE que no haya sido procesada.
        Esto asegura que el buffer esté completamente vacío antes de solicitar nueva entrada del usuario, evitando errores o lecturas no deseadas.
    */
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    FlushConsoleInputBuffer(hStdin);
}

void limpiarPantalla()
{
    system("cls");
}

void pausa()
{
    system("pause");
}

void mostrarTemporizador(unsigned int tiempo)
{
    printf("\n");
    while (tiempo > 0)
    {
        printf("\rTiempo restante: %2u", tiempo);
        fflush(stdout);
        Sleep(1000);
        tiempo--;
    }
}

void ocultarCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Ocultar el cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void mostrarCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = TRUE; // Mostrar el cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void mostrarTitulo()
{
    const char *titulo = "CMON DICE";
    int anchoConsola = 100; // Ajusta según necesites
    int longitudTitulo = strlen(titulo);
    int espacioIzquierdo = (anchoConsola - longitudTitulo) / 2;

    limpiarPantalla();
    printf("\033[1;34m"); // Color azul y negrita
    printf("%*s%s%*s\n", espacioIzquierdo - 1, "", titulo, espacioIzquierdo, "");
    printf("***************************************************************************************************\n\n");
    printf("\033[0m"); // Restablecer el color

}

int menuSeleccionable(const char *options[], int numOptions)
{

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
                iniciar_reproduccion_sonido_temporal(NAV_SOUND_NAME);
            }
            else if (key == DOWN_ARROW && selectedOption < numOptions - 1)
            {
                selectedOption++;
                iniciar_reproduccion_sonido_temporal(NAV_SOUND_NAME);
            }
        }

    }
    while(key != '\r' && key != ESCAPE);

    if (key == '\r') iniciar_reproduccion_sonido_temporal(MENUENTER_SOUND_NAME);

    if (key == ESCAPE) return ESCAPE;
    return selectedOption;
}

void displayMenu(const char *options[], int numOptions, int selectedOption)
{
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
