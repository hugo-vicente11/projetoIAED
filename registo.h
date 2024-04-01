#ifndef REGISTO_H
#define REGISTO_H
#include "structs.h"

void adicionaRegistoNode(RegCarroList *registos, RegCarroNode *registo);
RegCarroNode *obterRegNode(RegCarroList registos, 
						   char matricula[TAMMATRICULA+1], char *nParque);
int recolheNodesMat(RegCarroList *registos, char matricula[TAMMATRICULA+1],
				  RegCarroNode *lista[]);
void merge(RegCarroNode *lista[], int inicio, int meio, int fim);
void organizaNom(RegCarroNode *lista[], int inicio, int fim);
void mergeDataS(RegCarroNode *lista[], int esquerda, int meio, int direita);
void mergeSortDataS(RegCarroNode *lista[], int esquerda, int direita);
void organizaDataS(RegCarroNode *lista[], int tamanho);
void organizaDataE(RegCarroNode *lista[], int tamanho);
void iniciaV(char *matricula, RegCarroList registos);
void extraiArgsF(char *input, char nParque[BUFSIZ], char data[TAMDATA + 1]);
int recolheNodesNome(RegCarroList *registos, char *nParque,
					 RegCarroNode *lista[]);
int recolheNodesNomData(RegCarroList *registos, char *nParque,
						char data[TAMDATA+1], RegCarroNode *lista[]);
void iniciaF(char *input, RegCarroList *registos, parkList* parques,
			 char dataAnt[TAMDATA+1], char dataAntS[TAMDATA+1]);

#endif // REGISTO_H
