#ifndef MUSICA_H_INCLUDED
#define MUSICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>

#define SONGS_FOLDER "songs"
#define SONG_NAME "songs/arcade.mp3"
#define SUCCESS_SOUND_NAME "songs/success.mp3"
#define FAILURE_SOUND_NAME "songs/failure.mp3"
#define GAMEOVER_SOUND_NAME "songs/gameover.mp3"
#define NAV_SOUND_NAME "songs/nav.mp3"
#define MENUENTER_SOUND_NAME "songs/menu.mp3"
#define MAX_PATH_LENGTH 260
#define VOLUMEN_SYSTEM 20
#define VOLUMEN_DELAY_OFFSET 50

void reproducir_musica(const char *archivo);
void detener_musica();
void iniciar_reproduccion_sonido_temporal(const char *archivo);
DWORD WINAPI reproducir_sonido_temporal(LPVOID archivo);
void ajustar_volumen(int nivel, char *alias);

#endif // MUSICA_H_INCLUDED
