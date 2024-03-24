#ifndef PARQUE_H
#define PARQUE_H
#include "structs.h"

int processaInputP(char *frase, Parque *parque);
char custoInvalido(Parque *parque);
void iniciaP(char *resposta, parkList *parques);
void adicionaParkNode(parkList *parques, Parque *parque);
void removeParkNode(parkList *parques, char *nome);
void listaParques(parkList parques);
char parqueExiste(parkList parques, char *nome);
parkNode *obterParkNode(parkList parques, char *nome);


#endif