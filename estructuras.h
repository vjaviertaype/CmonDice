#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

// tJugadore es utilizado para guardar el nombre y los puntos
typedef struct
{
    char nombre_jugador[16];
    int puntos;
} tJugador;

// tRonda es necesario para llevar registro de cada movimiento del jugador
typedef struct
{
    unsigned int vidas_total;
    unsigned int vidas_consumidas;
    unsigned int puntos_turno;
} tRonda;


#endif // ESTRUCTURAS_H_INCLUDED
