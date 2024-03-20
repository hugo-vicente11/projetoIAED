#ifndef PARQUE_H
#define PARQUE_H


typedef struct {
    char *nome;
    int capMaxima, lugaresDisp;
    float val15, val15a1h, valMaxDia;
} Parque;


typedef struct parkNode{
    Parque parque;
    struct parkNode *next;
} parkNode;

typedef struct {
    parkNode *head;
    int tamanho;
} parkList;


#define MAX 20 // Maximo de parques de estacionamento


char custoInvalido(Parque *parque);
void iniciaP(char *resposta, parkList *parques);
void adicionaParkNode(parkList *parques, Parque *parque);
void removeParkNode(parkList *parques, char *nome);
void listaParques(parkList parques);
char parqueExiste(parkList parques, char *nome);


#endif