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

    limpiarPantalla();
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

    printf("\033[1;34m"); // Color azul y negrita
    printf("%*s%s%*s\n", espacioIzquierdo, "", titulo, espacioIzquierdo, "");
    printf("***************************************************************************************************\n\n");
    printf("\033[0m"); // Restablecer el color

}


