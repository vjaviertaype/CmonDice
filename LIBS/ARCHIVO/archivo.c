#include "archivo.h"

FILE* inicializarInforme(const char *nombre)
{
    FILE *pf;

    char nombre_generado[51];
    char fecha[17];
    obtenerFechaDeAhora(fecha, sizeof(fecha));

    snprintf(nombre_generado, sizeof(nombre_generado), "%s%s%s%s", nombre, SEPARADOR, fecha, EXTENSION);

    pf = fopen(nombre_generado,"wt");
    if(!pf) return NULL;

    fprintf(pf,"Fecha: %s\n",fecha);

    return pf;
}

int generarCabeceraJugador(FILE *info,int pos,char *nombre)
{
    return fprintf(info, "Jugador %d: %s\n", pos, nombre);
}

int generarCabezeraRonda(FILE *info,tRonda *ronda_actual)
{

    return fprintf(info, "Cantidad de vidas: %u\nSecuencia\t|Respuesta\t|Puntaje Actual\t|Vidas Usadas\t\n",ronda_actual->vidas_total);
}

void guardarRonda(FILE *info,tRonda *ronda_actual,tLista *sec_actual, tLista *respuesta)
{
    if(!listaVacia(sec_actual)) mapLista(sec_actual,info,imprimirCaracterEnArchivo);
    else fprintf(info,"-");

    fprintf(info,"\t|");

    if(!listaVacia(respuesta)) mapLista(respuesta,info,imprimirCaracterEnArchivo);
    else fprintf(info,"-");

    fprintf(info,"\t|");

    fprintf(info,"%u\t|",ronda_actual->puntos_turno);
    fprintf(info,"%d\n",ronda_actual->vidas_consumidas);
}

void imprimirCaracterEnArchivo(void *caracter,void *archivo)
{
    fprintf((FILE *)archivo,"%c",*(char*)caracter);
}


int finalizarInforme(FILE *info, tLista *p_jugadores,Cmp comparar)
{

    tJugador jugador_actual;
    int puntaje_prev,pos;

    puntaje_prev = pos = 0;
    fprintf(info,"Tabla de Puntaje\n");
    while(!listaVacia(p_jugadores))
    {
        sacarPrimeroLista(p_jugadores,&jugador_actual,sizeof(tJugador));
        if(comparar(&puntaje_prev,&jugador_actual.puntos) != 0)
        {
            fprintf(info,"\n");
            fprintf(info,"%d - %s",pos + 1,jugador_actual.nombre_jugador);
            pos++;
        }
        else
        {
            fprintf(info,", %s",jugador_actual.nombre_jugador);
        }
        puntaje_prev = jugador_actual.puntos;
    }

    fclose(info);
    return 1;
}
