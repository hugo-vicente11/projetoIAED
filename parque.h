#ifndef PARQUE_H
#define PARQUE_H
#include "structs.h"

char custoInvalido(Parque *parque);
void iniciaP(char *resposta, parkList *parques);
void adicionaParkNode(parkList *parques, Parque *parque);
parkNode *obterParkNode(parkList parques, char *nome);
void processaInputP(char *frase, Parque *parque);
void removeParkNode(parkList *parques, char *nome);
void listaParques(parkList parques);
char removeParque(parkList *parques, char *nome);
int extraiNomeParques(parkList *parques, char *lista[]);
void ordenaNomeParques(char *lista[], int tamanho);
void removeRegistosParque(RegCarroList *registos, char *nome);
void iniciaR(char *resposta, RegCarroList *registos, parkList *parques);

#endif
