#ifndef API_H_INCLUDED
#define API_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

void inicializa_manejo_curl(CURL**curl);
int respuesta_api(CURL*curl,CURLcode*,const char*url,int*);
size_t mi_write_call_back(void *contents, size_t size, size_t nmemb, void *userp);
void limpia_y_cierra_api (CURL*);
char convierteNumeroAletra(int num);

#endif // API_H_INCLUDED
