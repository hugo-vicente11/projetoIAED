#include "parque.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"


/**
 * @brief Verifica se os valores de custo de um parque são inválidos.
 * 
 * Esta função verifica se os valores de custo de um parque são negativos 
 * ou se não seguem a ordem esperada (val15 < val15a1h < valMaxDia).
 * 
 * @param parque Ponteiro para o parque a ser verificado.
 * @return Retorna 1 se os valores de custo forem inválidos, 0 caso contrário.
 */
char custoInvalido(Parque *parque) {
    return (parque->val15 < 0 || parque->val15a1h < 0 || 
            parque->valMaxDia < 0 ||
            !((parque->val15 < parque->val15a1h) &&
            (parque->val15a1h < parque->valMaxDia)));
}


/**
 * @brief Inicia um novo parque de estacionamento.
 * 
 * Esta função processa a resposta do usuário para iniciar um novo parque. 
 * Verifica se o número máximo de parques foi atingido, se o parque já 
 * existe, se a capacidade máxima é válida e se os custos são válidos. 
 * Se todas as verificações passarem, o parque é adicionado à lista de parques.
 * 
 * @param resposta Resposta do usuário.
 * @param parques Lista de parques.
 */
void iniciaP(char *resposta, parkList *parques) {
    if (strlen(resposta) <= 2) {
        listaParques(*parques);
        return;
    }

    if (parques->tamanho >= MAX) {
        printf("too many parks.\n");
        return;
    }

    Parque novoParque = { 
    .nome = NULL, 
    .capMaxima = 0, 
    .lugaresDisp = 0, 
    .val15 = 0.0f, 
    .val15a1h = 0.0f, 
    .valMaxDia = 0.0f, 
    .carros = {NULL, 0}
    };

    processaInputP(resposta, &novoParque);
    if (parques->tamanho != 0) {
        if (obterParkNode(*parques, novoParque.nome) != NULL){
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


/**
 * @brief Adiciona um novo nó de parque à lista de parques.
 * 
 * Esta função cria um novo nó de parque e o adiciona ao final da lista de 
 * parques. Se a lista estiver vazia, o novo nó se torna a cabeça da lista. 
 * O tamanho da lista é incrementado após a adição do novo nó.
 * 
 * @param parques Ponteiro para a lista de parques.
 * @param parque Ponteiro para o parque a ser adicionado à lista.
 */
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


/**
 * @brief Obtém um nó de parque com base no nome.
 * 
 * Esta função percorre a lista de parques e retorna o nó de parque que 
 * corresponde ao nome fornecido. Se o parque não for encontrado, retorna NULL.
 * 
 * @param parques Lista de parques a serem pesquisados.
 * @param nome Nome do parque a ser encontrado.
 * @return Retorna pointer para o nó do parque, NULL caso contrário.
 */
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


/**
 * @brief Processa a entrada do usuário para a criação de um parque.
 * 
 * Esta função processa a entrada do usuário para a criação de um parque. 
 * Extrai o nome do parque, a capacidade máxima e os valores de custo do 
 * estacionamento da entrada do usuário. O nome do parque é alocado 
 * dinamicamente.
 * 
 * @param frase Entrada do usuário.
 * @param parque Ponteiro para o parque a ser preenchido com os dados.
 */
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


/**
 * @brief Remove um nó de parque da lista de parques.
 * 
 * Esta função percorre a lista de parques e remove o nó de parque que 
 * corresponde ao nome fornecido. Se o parque for a cabeça da lista, a 
 * cabeça é atualizada para o próximo nó. O nome do parque e o nó são 
 * liberados da memória após a remoção.
 * 
 * @param parques Ponteiro para a lista de parques.
 * @param nome Nome do parque a ser removido.
 */
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
        if (saoIguais(atual->parque.nome, nome, tamanho,
            strlen(atual->parque.nome))) {
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


/**
 * @brief Lista todos os parques de estacionamento.
 * 
 * Esta função percorre a lista de parques e imprime o nome, a capacidade 
 * máxima e os lugares disponíveis de cada parque.
 * 
 * @param parques Lista de parques a serem listados.
 */
void listaParques(parkList parques) {
    parkNode *atual = parques.head;
    while (atual != NULL) {
        printf("%s %d %d\n", atual->parque.nome, atual->parque.capMaxima,
               atual->parque.lugaresDisp);
        atual = atual->next;
    }
    return;
}


/**
 * @brief Remove um parque da lista de parques.
 * 
 * Esta função percorre a lista de parques e remove o parque com o nome 
 * fornecido. Todos os carros no parque são removidos e a memória é liberada. 
 * Se o parque a ser removido é a cabeça da lista, a cabeça é atualizada.
 * 
 * @param parques Ponteiro para a lista de parques.
 * @param nome Nome do parque a ser removido.
 * @return Retorna 1 se o parque foi removido, 0 se não foi encontrado.
 */
char removeParque(parkList *parques, char *nome) {
    parkNode *atual = parques->head;
    parkNode *anterior = NULL;
    int tamanho = strlen(nome);
    while (atual != NULL) {
        if (saoIguais(atual->parque.nome, nome, strlen(atual->parque.nome),
            tamanho)) {
            CarroNode *carroAtual = atual->parque.carros.head;
            CarroNode *carroAnterior = NULL;
            while (carroAtual != NULL) {
                carroAnterior = carroAtual;
                carroAtual = carroAtual->next;
                free(carroAnterior);
            }
            if (anterior == NULL) {
                parques->head = atual->next;
            } else {
                anterior->next = atual->next;
            }
            free(atual->parque.nome);
            parkNode *temp = atual;
            atual = atual->next;
            free(temp);
            parques->tamanho--;
            return 1; // Parque removido
        } else {
            anterior = atual;
            atual = atual->next;
        }
    }
    return 0; // parque nao encontrado
}


/**
 * @brief Extrai os nomes dos parques da lista de parques.
 * 
 * Esta função percorre a lista de parques e extrai o nome de cada parque. 
 * Os nomes são armazenados no array de strings fornecido.
 * 
 * @param parques Ponteiro para a lista de parques.
 * @param lista Array de strings para armazenar os nomes dos parques.
 */
int extraiNomeParques(parkList *parques, char *lista[]) {
    parkNode *atual = parques->head;
    int i = 0;
    while (atual != NULL) {
        lista[i] = strcpy(lista[i], atual->parque.nome);
        atual = atual->next;
        i++;
    }
    return i;
}


/**
 * @brief Ordena os nomes dos parques em ordem alfabética.
 * 
 * Esta função recebe um array de strings e o seu tamanho. Utiliza o 
 * algoritmo de ordenação por bolha para ordenar os nomes dos parques 
 * em ordem alfabética.
 * 
 * @param lista Array de strings contendo os nomes dos parques.
 * @param tamanho Número de nomes no array.
 */
void ordenaNomeParques(char *lista[], int tamanho) {
    char *temp;
    for (int i = 0; i < tamanho; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (strcmp(lista[i], lista[j]) > 0) {
                temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }
    return;
}


/**
 * @brief Remove todos os registos de um parque específico.
 * 
 * Esta função percorre a lista de registos de carros e remove todos os 
 * registos que correspondem ao nome do parque fornecido. Se o registo a 
 * ser removido é a cabeça da lista, a cabeça é atualizada. O nome do parque 
 * e o nó do registo são liberados da memória após a remoção.
 * 
 * @param registos Ponteiro para a lista de registos de carros.
 * @param nome Nome do parque cujos registos devem ser removidos.
 */
void removeRegistosParque(RegCarroList *registos, char *nome) {
    RegCarroNode *atual = registos->head;
    RegCarroNode *anterior = NULL;
    int tamanho = strlen(nome);
    while (atual != NULL) {
        if (saoIguais(atual->regCarro.nParque, nome, 
        strlen(atual->regCarro.nParque), tamanho)) {
            if (anterior == NULL) {
                registos->head = atual->next;
            } else {
                anterior->next = atual->next;
            }
            RegCarroNode *temp = atual;
            atual = atual->next;
            free(temp->regCarro.nParque);
            free(temp);
            registos->tamanho--;
        } else {
            anterior = atual;
            atual = atual->next;
        }
    }
}


/**
 * @brief Processa a resposta do usuário para remover um parque.
 * 
 * Esta função processa a resposta do usuário para remover um parque. 
 * Extrai o nome do parque da resposta, remove todos os registos de carros 
 * do parque e remove o parque da lista de parques. Se o parque não existir, 
 * imprime uma mensagem de erro. Após a remoção, lista todos os parques 
 * restantes em ordem alfabética.
 * 
 * @param resposta Resposta do usuário.
 * @param registos Ponteiro para a lista de registos de carros.
 * @param parques Ponteiro para a lista de parques.
 */
void iniciaR(char *resposta, RegCarroList *registos, parkList *parques) {
    char temp[BUFSIZ];
    int numParques, tamanho;
    if (temAspas(resposta)) {
        sscanf(resposta, "r \"%[^\"]\"", temp);
    } else {
        sscanf(resposta, "r %s", temp);
    }
    removeRegistosParque(registos, temp);
    if (!removeParque(parques, temp)) {
        printf("%s: no such parking.\n", temp);
        return;
    }
    numParques = parques->tamanho;
    char *lista[numParques];
    for (int i = 0; i < numParques; i++) {
        lista[i] = (char*)malloc(100);
    }
    tamanho = extraiNomeParques(parques, lista);
    ordenaNomeParques(lista, tamanho);

    for (int i = 0; i < tamanho; i++) {
        printf("%s\n", lista[i]);
    }

    for (int i = 0; i < numParques; i++) {
        free(lista[i]);
    }
    return;
}


