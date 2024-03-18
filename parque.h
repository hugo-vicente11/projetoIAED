#ifndef PARQUE_H
#define PARQUE_H


typedef struct {
    char *nome;
    int capMaxima, lugaresDisp;
    float val15, val15a1h, valMaxDia;
} Parque;


#define MAX 20 // Maximo de parques de estacionamento

void listaParques(Parque parques[], int nParques);
char custoInvalido(Parque *parque);
char parqueExiste(Parque parques[], int nParques,char *nome);
void iniciaP(char *resposta, Parque parques[], int *nParques);


#endif