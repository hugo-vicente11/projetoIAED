#ifndef STRUCTS_H
#define STRUCTS_H

#define TAMMATRICULA 8
#define TAMDATA 10
#define TAMHORA 5
#define MAX 20
#define HASHSIZE 5003


typedef struct {
    char matricula[TAMMATRICULA+1], dataEntrada[TAMDATA+1],
    horaEntrada[TAMHORA+1];
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


typedef struct RegCarro {
    char *matricula;
    char tipo; // e - entrada, s - saida
    char data[TAMDATA+1], hora[TAMHORA+1];
} RegCarro;


typedef struct RegCarroNode {
    RegCarro regCarro;
    struct RegCarroNode *next;
} RegCarroNode;


typedef struct {
    RegCarroNode *head;
    int tamanho;
} RegCarroList;

#endif // STRUCTS_H