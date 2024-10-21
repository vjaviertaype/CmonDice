#include "api.h"

int main()
{

    CURL *curl;
    CURLcode res;
    int num;
    const char * url = "https://www.random.org/integers/?num=1&min=1&max=4&col=1&base=10&format=plain&rnd=new";

    inicializa_manejo_curl(&curl);
    for(int i=0;i<4;i++){
        respuesta_api(curl,&res,url,&num);
        imprime_color(num);
    }

    limpia_y_cierra_api(curl);


    return 0;
}
