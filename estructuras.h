#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

//Datos para usar con cronometro "Hilos"
typedef struct {
    unsigned int* tiempo_turno;
    int* continuar;
} Datos;

typedef struct
{
	char nombre_jugador[16];
	int puntos;
}tJugador;

//tRonda es necesario para llevar registro de cada movimiento del jugador
typedef struct
{
	unsigned int vidas_total;
	unsigned int vidas_consumidas;
	unsigned int puntos_turno;
}tRonda;


#endif // ESTRUCTURAS_H_INCLUDED
