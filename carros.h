#ifndef CARROS_H
#define CARROS_H
#include "parque.h"

typedef struct {
    char *matricula;
    int horaEntrada, minutoEntrada;
    int horaSaida, minutoSaida;
    float custo;
} Carro;


void iniciaE(char *resposta, Parque parques[], int *lugaresDisp);
char matriculaValida(char *matricula);
char avaliaCaracteres(char c1, char c2);


#endif