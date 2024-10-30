#include "musica.h"

void reproducir_musica(const char *archivo) {
    char command[256];
    snprintf(command, sizeof(command), "open \"%s\" type mpegvideo alias musica", archivo);
    mciSendString(command, NULL, 0, NULL);
    mciSendString("play musica repeat", NULL, 0, NULL);
    ajustar_volumen(VOLUMEN_SYSTEM,"musica");
}

void ajustar_volumen(int nivel,char *alias) {
    char comando[64];
    snprintf(comando, sizeof(comando), "setaudio %s volume to %d", alias , nivel);
    mciSendString(comando, NULL, 0, NULL);
}
void detener_musica() {
    mciSendString("stop musica", NULL, 0, NULL);
    mciSendString("close musica", NULL, 0, NULL);
}

DWORD WINAPI reproducir_sonido_temporal(LPVOID archivo) {
    char command[256];
    snprintf(command, sizeof(command), "open \"%s\" type mpegvideo alias sonidoTemporal", (char *)archivo);
    if (mciSendString(command, NULL, 0, NULL) != 0) {
        printf("Error al abrir el sonido: %s\n", (char *)archivo);
        return 1; // Código de error
    }
    if (mciSendString("play sonidoTemporal", NULL, 0, NULL) != 0) {
        printf("Error al reproducir el sonido temporal.\n");
        return 1; // Código de error
    }

    // Puedes quitar o ajustar Sleep si el sonido es corto
    ajustar_volumen(VOLUMEN_SYSTEM + VOLUMEN_DELAY_OFFSET,"sonidoTemporal");
    Sleep(2000); // O ajustar a la duración real del sonido

    mciSendString("close sonidoTemporal", NULL, 0, NULL);
    return 0;
}

void iniciar_reproduccion_sonido_temporal(const char *archivo) {
    HANDLE hilo;
    hilo = CreateThread(NULL, 0, reproducir_sonido_temporal, (LPVOID)archivo, 0, NULL);
    if (hilo == NULL) {
        printf("Error creando el hilo.\n");
    } else {
        CloseHandle(hilo); // Opcional: cerrar el handle del hilo si no necesitas esperar
    }
}
