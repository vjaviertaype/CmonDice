#include "ganadores.h"

int cargarPilaGanadores(tPila* pilaG, tJugador* jugador, Cmp cmp)
{
    tJugador pj;
    int comp;

    if(jugador->puntos == 0)
        return JUGADOR_SIN_PUNTOS;

    if(pilaVacia(pilaG))
    {
        ponerEnPila(pilaG, jugador, sizeof(tJugador));
        return PRIMER_INGRESO;
    }

    verTope( pilaG, &pj, sizeof(tJugador) );
    comp = cmp(jugador, &pj);

    if(comp == 0)
    {
        ponerEnPila(pilaG, jugador, sizeof(tJugador));
    }
    else if(comp > 0)
    {
        vaciarPila(pilaG);
        ponerEnPila(pilaG, jugador, sizeof(tJugador));
    }

    return JUGADOR_NO_SUPERA_MAYOR_PUNTAJE;
}

int mostrarGanadores(tPila* pilaG)
{
    tJugador pj;
    tPila pilaAux;
    int cont = 0;

    limpiarPantalla();
    crearPila(&pilaAux);
    if(pilaVacia(pilaG))
    {
        printf("\033[1;31m");
        mostrarArteASCII(SIN_GANADORES);
        printf("\033[0;37m"); // Blanco normal
        puts("\n\n");
    }
    else
    {
        while(sacarDePila(pilaG,&pj, sizeof(tJugador)))
        {
            cont++;
            ponerEnPila(&pilaAux, &pj, sizeof(tJugador));
        }

        if(cont == 1)
        {
            printf("\033[1;32m"); // Verde y en negrita
            mostrarArteASCII(GANADOR);
            printf("\033[0;37m"); // Blanco normal
            printf("\n\n\t\t\t%s - %d puntos \n\n\n",pj.nombre_jugador, pj.puntos);

        }
        else if( cont > 1)
        {
            printf("\033[1;32m"); // Verde y en negrita
            mostrarArteASCII(GANADORES);
            printf("\033[0;37m"); // Blanco normal
            puts("\n\n");
            while(sacarDePila(&pilaAux,&pj, sizeof(tJugador)))
            {
                printf("\n\t\t\t\t- %s",pj.nombre_jugador);
            }
            printf("\n\t\t\t\tpuntos %d\n\n",pj.puntos);
        }

    }

    vaciarPila(&pilaAux);
    vaciarPila(pilaG);

    return HUBO_GANADOR;
}
