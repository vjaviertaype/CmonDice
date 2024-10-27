#include "comun.h"
#include "TDA_LISTA/lista.h"

void obtenerFechaDeAhora(char *buffer, unsigned tam) {
    time_t tiempoActual = time(NULL);
    struct tm *infoTiempo = localtime(&tiempoActual);

    strftime(buffer, tam, "%Y-%m-%d-%H-%M", infoTiempo);
}
///Funcion que limpia el buffer de teclado en su totalidad...
void limpiarBufferTeclado()
{

    fflush(stdin);
    /**fflush solo limpia el buffer de teclado hasta encontrar un salto de linea (\n), Eso significa que
        ... cualquier cosa despu�s del primer "\n" permanecer� en el buffer.
        Ejemplo : si el usuario escribio por teclado : "xrty\n\n\nrb\n"
        fflush(stdin) solo borrara "xrty\n", pero en el buffer de teclado seguira quedando "\n\nrb\n"

    Para solucionar esto :
        La librer�a windows.h proporciona funciones espec�ficas para la interacci�n con el sistema operativo Windows.
        En este caso, utilizamos GetStdHandle para obtener el "handle" o manejador del buffer de entrada de la consola (STD_INPUT_HANDLE)
        ... y FlushConsoleInputBuffer para limpiar dicho buffer, eliminando cualquier entrada PENDIENTE que no haya sido procesada.
        Esto asegura que el buffer est� completamente vac�o antes de solicitar nueva entrada del usuario, evitando errores o lecturas no deseadas.
    */
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    FlushConsoleInputBuffer(hStdin);
}

void limpiarPantalla()
{
#ifdef _WIN32
    /// Si es Windows
    system("cls");  /// Limpia la pantalla en Windows
#else
    /// Para Linux y otros sistemas POSIX
    system("clear"); /// Limpia la pantalla en Linux
#endif
}

void pausa()
{
#ifdef _WIN32
    /// Si es Windows
    system("pause"); /// Pausa en Windows
#else
    /// Para Linux y otros sistemas POSIX
    printf("Presione Enter para continuar...");
    getchar();  /// Espera a que el usuario presione Enter
#endif
}
