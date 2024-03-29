#include "parque.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

char custoInvalido(Parque *parque) {
    return (parque->val15 < 0 || parque->val15a1h < 0 || 
            parque->valMaxDia < 0 ||
            !((parque->val15 < parque->val15a1h) &&
            (parque->val15a1h < parque->valMaxDia)));
}


char parqueExiste(parkList parques, char *nome) {
    int tamanho = strlen(nome);
    parkNode *atual = parques.head;
    while (atual != NULL) {
        if (saoIguais(atual->parque.nome, nome, tamanho, 
            strlen(atual->parque.nome)))
        {
            return 1;
        }
        atual = atual->next;
    }
    return 0;
}


void iniciaP(char *resposta, parkList *parques) {
    if (strlen(resposta) <= 2) {
        listaParques(*parques);
        return;
    }

    if (parques->tamanho >= MAX) {
        printf("too many parks.\n");
        return;
    }

    Parque novoParque;
    processaInputP(resposta, &novoParque);
    if (parques->tamanho != 0) {
        if (parqueExiste(*parques, novoParque.nome)) {
            printf("%s: parking already exists.\n",novoParque.nome);
            return;
        }
    }
    
    if (novoParque.capMaxima <= 0) {
        printf("%d: invalid capacity.\n", novoParque.capMaxima);
        return;
    }

    if (custoInvalido(&novoParque)) {
        printf("invalid cost.\n");
        return;
    }

    novoParque.lugaresDisp = novoParque.capMaxima;
    adicionaParkNode(parques, &novoParque);
    return;
}


void adicionaParkNode(parkList *parques, Parque *parque) {
    parkNode *novo = (parkNode*)malloc(sizeof(parkNode));
    novo->parque = *parque;
    novo->next = NULL;
    if (parques->head == NULL) {
        parques->head = novo;
    } else {
        parkNode *atual = parques->head;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novo;
    }
    parques->tamanho++;
    return;
}


parkNode *obterParkNode(parkList parques, char *nome) {
    int tamanho = strlen(nome);
    parkNode *atual = parques.head;
    while (atual != NULL) {
        if (saoIguais(atual->parque.nome, nome, tamanho, 
            strlen(atual->parque.nome)))
        {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}


void processaInputP(char *frase, Parque *parque) {
    char temp[BUFSIZ];

    if (temAspas(frase)) {
        sscanf(frase, "p \"%8191[^\"]\" %d %f %f %f",temp, 
                           &parque->capMaxima,&parque->val15, 
                           &parque->val15a1h, &parque->valMaxDia);
    } else {
        sscanf(frase, "p %8191[^ ] %d %f %f %f", temp, 
                           &parque->capMaxima, &parque->val15, 
                           &parque->val15a1h, &parque->valMaxDia);
    }
    parque->nome = (char*)malloc((strlen(temp) + 1));
    strcpy(parque->nome, temp);
    return;
}


void removeParkNode(parkList *parques, char *nome) {
    int tamanho = strlen(nome);
    if (parques->head == NULL) {
        return;
    }

    if (parques->tamanho == 0) {
        return;
    }

    parkNode *atual = parques->head;
    parkNode *anterior = NULL;
    while (atual != NULL) {
        if (saoIguais(atual->parque.nome, nome, tamanho, strlen(atual->parque.nome))) {
            if (anterior == NULL) {
                parques->head = atual->next;
            } else {
                anterior->next = atual->next;
            }
            free(atual->parque.nome);
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
    return;
}


void listaParques(parkList parques) {
    if (parques.tamanho == 0) {
        printf("No parking lots.\n");
        return;
    }

    parkNode *atual = parques.head;
    while (atual != NULL) {
        printf("%s %d %d\n", atual->parque.nome, atual->parque.capMaxima,
               atual->parque.lugaresDisp);
        atual = atual->next;
    }
    return;
}
