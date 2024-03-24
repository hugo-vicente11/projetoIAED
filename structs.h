#ifndef STRUCTS_H
#define STRUCTS_H

#define TAMMATRICULA 8
#define MAX 20


typedef struct {
    char matricula[TAMMATRICULA+1], dataEntrada[11], horaEntrada[6];
    float custo;
} Carro;


typedef struct CarroNode {
    Carro carro;
    struct CarroNode *next;
} CarroNode;


typedef struct {
    CarroNode *head;
    int tamanho;
} CarroList;


typedef struct {
    char *nome;
    int capMaxima, lugaresDisp;
    float val15, val15a1h, valMaxDia;
    CarroList carros;
} Parque;


typedef struct parkNode{
    Parque parque;
    struct parkNode *next;
} parkNode;


typedef struct {
    parkNode *head;
    int tamanho;
} parkList;


#endif // STRUCTS_H