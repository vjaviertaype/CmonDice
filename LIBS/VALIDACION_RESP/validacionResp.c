#include"validacionResp.h"

int validacionRespuesta(tLista* l_sec, tLista* l_resp)
{
    if(listaVacia(l_sec))
        return ERROR_FATAL; //error fatal - la lista de secuencia nunca deberia estar vacia
    if(listaVacia(l_resp))
        return NO_CONTESTA; //Si el jugador no contesto.

    char resp;
    verUltimoLista(l_resp,&resp, sizeof(char));
    resp = toupper(resp);
    if( resp == 'Z' )
    {
        sacarUltimoLista(l_resp,&resp, sizeof(char));
        return USO_CARACTER_ESPECIAL;//El jugador apreto apreto caracter especial
    }

    if(listasIguales(l_sec, l_resp, cmpChar) == 0 )
        return RESPUESTA_INCORRECTA;

    return RESPUESTA_CORRECTA;//La respuesta coincide con la secuencia mostrada en pantalla
}

int cmpChar(const void* e1, const void* e2)
{
    char a1 = *((char*)e1);
    char a2 = *((char*)e2);

    return a1 - a2;
}
