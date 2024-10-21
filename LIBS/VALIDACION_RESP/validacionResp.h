#ifndef VALIDACIONRESP_H_INCLUDED
#define VALIDACIONRESP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

///Incluir ruta de lista correcta
#include "../TDA_LISTA/lista.h"

#define ERROR_FATAL -1
#define RESPUESTA_CORRECTA 1
#define RESPUESTA_INCORRECTA 2
#define USO_CARACTER_ESPECIAL 3
#define NO_CONTESTA 4

int cmpChar(const void* e1, const void* e2);

int validacionRespuesta(tLista* l_sec, tLista* l_resp);


#endif // VALIDACIONRESP_H_INCLUDED
