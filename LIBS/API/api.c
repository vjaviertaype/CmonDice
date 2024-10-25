#include "api.h"

void inicializa_manejo_curl(CURL**curl)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    *curl = curl_easy_init();
}

int respuesta_api(CURL *curl,CURLcode *res,const char *url,int *num)
{
    if(!curl)
        return 0;

    {
// Establecer la URL de la solicitud GET
        curl_easy_setopt(curl, CURLOPT_URL, url);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "X: Y");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
// Establecer la función de retorno de llamada para manejar la respuesta
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, mi_write_call_back);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)num);  // Pasar puntero a número
// Realizar la solicitud HTTP GET
        *res = curl_easy_perform(curl);
// Verificar si la solicitud fue exitosa
        if (res == CURLE_OK)
        {
            fprintf(stderr, "Error en la solicitud: %s\n",
                    curl_easy_strerror(*res));
        }

        return 1;
    }
}



size_t mi_write_call_back(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    int *numero = (int *)userp;  // Convertir userp a un puntero a int
    char *respuesta = (char *)contents;

    int numeroObtenido = atoi(respuesta);

    *numero = numeroObtenido;     // Almacenar el número obtenido


    return realsize;
}


void limpia_y_cierra_api (CURL*curl)
{
    // Limpiar y cerrar el manejo de curl
    curl_easy_cleanup(curl);
// Finalizar el manejo global de curl
    curl_global_cleanup();
}

char convierteNumeroAletra(int num)
{
    switch(num)
    {
    case 1:
        return 'R';
        break;
    case 2:
        return 'A';
        break;
    case 3:
        return 'V';
        break;
    case 4:
        return 'N';
        break;
    }

    return '\0';
}
