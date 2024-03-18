#include "parque.h"
#include "lib.h"
#include <stdio.h>
#include <string.h>

void listaParques(Parque parques[], int nParques) {
    for (int i = 0; i < nParques; i++) {
        printf("%s %d %d\n", parques[i].nome, parques[i].capMaxima,
               parques[i].lugaresDisp);
    }
}


char custoInvalido(Parque *parque) {
    return (parque->val15 < 0 || parque->val15a1h < 0 || 
            parque->valMaxDia < 0 ||
            !((parque->val15 < parque->val15a1h) &&
            (parque->val15a1h < parque->valMaxDia)));
}


char parqueExiste(Parque parques[], int nParques, char *nome) {
    int tamanho = strlen(nome);
    for (int i = 0; i < nParques; i++) {
        if (saoIguais(parques[i].nome, nome, tamanho, strlen(parques[i].nome)))
            return 1;
    }
    return 0;
}


void iniciaP(char *resposta, Parque parques[], int *nParques) {
    if (strlen(resposta) == 1) {
        listaParques(parques, *nParques);
        return;
    }

    if (*nParques >= MAX) {
        printf("too many parks.\n");
        return;
    }

    Parque novoParque;
    if (processaInput(resposta + 2, &novoParque) != 5) {
        printf("Erro ao ler os valores.\n");
        return;
    }

    if (*nParques != 0) {
        if (parqueExiste(parques, *nParques, novoParque.nome)) {
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
    parques[*nParques] = novoParque;
    (*nParques)++;
    return;
}
