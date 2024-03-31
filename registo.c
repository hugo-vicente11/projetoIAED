#include "registo.h"
#include "structs.h"
#include "lib.h"
#include "parque.h"
#include "carros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adicionaRegistoNode(RegCarroList *registos, RegCarroNode *registo) {
	RegCarroNode *atual = registos->head;
	if (atual == NULL) {
		registos->head = registo;
		registos->tamanho++;
		return;
	}
	while (atual->next != NULL) {
		atual = atual->next;
	}
	atual->next = registo;
	registos->tamanho++;
}


RegCarroNode *obterRegNode(RegCarroList registos, 
						   char matricula[TAMMATRICULA+1], char *nParque) {
	RegCarroNode *atual = registos.head;
	int tamanho = strlen(nParque);
	while (atual != NULL) {
		if ((saoIguais(atual->regCarro.matricula, matricula, TAMMATRICULA,
		 	TAMMATRICULA)) && (saoIguais(atual->regCarro.nParque, nParque, 
			strlen(atual->regCarro.nParque), tamanho)) && 
			strcmp(atual->regCarro.dataS, "00-00-0000") == 0){
			return atual;
		}
		atual = atual->next;
	}
	return NULL;
}


/*void listaRegisto(RegCarroList registos, char matricula[TAMMATRICULA+1],
				  RegCarroNode* lista[], int tamanho) {
	int c = 0;
	RegCarroNode *atual = registos.head;

}*/


int recolheNodesMat(RegCarroList *registos, char matricula[TAMMATRICULA+1],
				  RegCarroNode *lista[]) {
	int c = 0;
	RegCarroNode *atual = registos->head;
	while (atual != NULL) {
		if (saoIguais(atual->regCarro.matricula, matricula, TAMMATRICULA,
			TAMMATRICULA)) {
			lista[c] = atual;
			c++;
		}
		atual = atual->next;
	}
	free(atual);
	return c;
}


void merge(RegCarroNode *lista[], int inicio, int meio, int fim) {
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    RegCarroNode *L[n1], *R[n2];

    for (i = 0; i < n1; i++)
        L[i] = lista[inicio + i];
    for (j = 0; j < n2; j++)
        R[j] = lista[meio + 1 + j];

    i = 0;
    j = 0;
    k = inicio;
    while (i < n1 && j < n2) {
        if (strcmp(L[i]->regCarro.nParque, R[j]->regCarro.nParque) <= 0) {
            lista[k] = L[i];
            i++;
        } else {
            lista[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        lista[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        lista[k] = R[j];
        j++;
        k++;
    }
}

void organizaNom(RegCarroNode *lista[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        organizaNom(lista, inicio, meio);
        organizaNom(lista, meio + 1, fim);

        merge(lista, inicio, meio, fim);
    }
}


void organizaDataS(RegCarroNode *lista[], int tamanho) {
    int i, j, anoI, mesI, diaI, horaI, minI, anoJ, mesJ, diaJ, horaJ, minJ;
    RegCarroNode *temp;
    for (i = 0; i < tamanho; i++) {
        converteData(lista[i]->regCarro.dataS, &anoI, &mesI, &diaI);
        converteHora(lista[i]->regCarro.horaS, &horaI, &minI);
        for (j = i+1; j < tamanho; j++) {
            converteData(lista[j]->regCarro.dataS, &anoJ, &mesJ, &diaJ);
            converteHora(lista[j]->regCarro.horaS, &horaJ, &minJ);
            if (anoI > anoJ || (anoI == anoJ && mesI > mesJ) || 
                (anoI == anoJ && mesI == mesJ && diaI > diaJ) ||
                (anoI == anoJ && mesI == mesJ && diaI == diaJ && horaI > horaJ) ||
                (anoI == anoJ && mesI == mesJ && diaI == diaJ && 
				horaI == horaJ && minI > minJ)) {
                temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }
}


void organizaDataE(RegCarroNode *lista[], int tamanho) {
	int i, j, anoI, mesI, diaI, horaI, minI, anoJ, mesJ, diaJ, horaJ, minJ;
	RegCarroNode *temp;
	for (i = 0; i < tamanho; i++) {
		converteData(lista[i]->regCarro.dataE, &anoI, &mesI, &diaI);
		converteHora(lista[i]->regCarro.horaE, &horaI, &minI);
		for (j = i+1; j < tamanho; j++) {
			converteData(lista[j]->regCarro.dataE, &anoJ, &mesJ, &diaJ);
			converteHora(lista[j]->regCarro.horaE, &horaJ, &minJ);
			if (anoI > anoJ || (anoI == anoJ && mesI > mesJ) || 
				(anoI == anoJ && mesI == mesJ && diaI > diaJ) ||
				(anoI == anoJ && mesI == mesJ && diaI == diaJ && horaI > horaJ) ||
				(anoI == anoJ && mesI == mesJ && diaI == diaJ && 
				horaI == horaJ && minI > minJ)) {
				temp = lista[i];
				lista[i] = lista[j];
				lista[j] = temp;
			}
		}
	}

}


void iniciaV(char *matricula, RegCarroList registos) {
	int indice;
	RegCarroNode *lista[registos.tamanho];
	matricula[TAMMATRICULA] = '\0';
	if (!matriculaValida(matricula)) {
		printf("%s: invalid licence plate.\n", matricula);
		return;
	}

	if ((indice = recolheNodesMat(&registos, matricula, lista)) == 0) {
		printf("%s: no entries found in any parking.\n", matricula);
		return;
	}

	organizaNom(lista, 0, indice-1);
	for (int i = 0; i < indice; i++) {
		int horaIntE, minIntE, horaIntS, minIntS;
		converteHora(lista[i]->regCarro.horaE, &horaIntE, &minIntE);
		converteHora(lista[i]->regCarro.horaS, &horaIntS, &minIntS);
		if (strcmp(lista[i]->regCarro.dataS, "00-00-0000") == 0) {
			printf("%s %s %s\n", lista[i]->regCarro.nParque,
			 	   lista[i]->regCarro.dataE, lista[i]->regCarro.horaE);
		} else {
			printf("%s %s %02d:%02d %s %02d:%02d\n",lista[i]->regCarro.nParque,
			lista[i]->regCarro.dataE, horaIntE, minIntE,
			lista[i]->regCarro.dataS, horaIntS, minIntS);
		}
	}

}


void extraiArgsF(char *input, char nParque[BUFSIZ], char data[TAMDATA + 1]) {
    int aspas = temAspas(input);
	if (aspas) {
		sscanf(input, "f \"%[^\"]\" %s", nParque, data);
	} else {
		sscanf(input, "f %s %s", nParque, data);
	}
}


int recolheNodesNome(RegCarroList *registos, char *nParque,
					 RegCarroNode *lista[]) {
	int c = 0;
	int tamanho = strlen(nParque);
	RegCarroNode *atual = registos->head;
	while (atual != NULL) {
		if (saoIguais(atual->regCarro.nParque, nParque,
			strlen(atual->regCarro.nParque), tamanho) &&
			!saoIguais(atual->regCarro.dataS, "00-00-0000", TAMDATA, TAMDATA)) {
			lista[c] = atual;
			c++;
		}
		atual = atual->next;
	}
	free(atual);
	return c;
}

// Funcao que adiciona o ponteiro do Node para o registo do carro a lista, caso o nome e data do parque sejam iguais
int recolheNodesNomData(RegCarroList *registos, char *nParque,
						char data[TAMDATA+1], RegCarroNode *lista[]) {
	int c = 0;
	int tamanho = strlen(nParque);
	RegCarroNode *atual = registos->head;
	while (atual != NULL) {
		if (saoIguais(atual->regCarro.nParque, nParque,
			strlen(atual->regCarro.nParque), tamanho) && 
			saoIguais(atual->regCarro.dataS, data, TAMDATA, TAMDATA)) {
			lista[c] = atual;
			c++;
		}
		atual = atual->next;
	}
	return c;
}


void iniciaF(char *input, RegCarroList *registos, parkList* parques,
			 char dataAnt[TAMDATA+1]) {
	char temp[BUFSIZ], data[TAMDATA+1];
	int horaIntS, minIntS, indice;
	int ano, mes, dia;
	RegCarroNode *lista[registos->tamanho];
	extraiArgsF(input, temp, data);
	char *nParque = (char*)malloc(strlen(temp)+1);
	strcpy(nParque, temp);
	converteData(data, &dia, &mes, &ano);

	if (obterParkNode(*parques, nParque) == NULL) {
		printf("%s: no such parking.\n", nParque);
		free(nParque);
		return;
	}

	if (strcmp(data, "") == 0) {
		Faturacao faturacao[registos->tamanho];
		int numDias = 0;
		indice = recolheNodesNome(registos, nParque, lista);
		organizaDataS(lista, indice);
		for (int i = 0; i < indice; i++) {
			converteHora(lista[i]->regCarro.horaS, &horaIntS, &minIntS);
			int j;
			for (j = 0; j < numDias; j++) {
				if (strcmp(faturacao[j].data, lista[i]->regCarro.dataS) == 0) {
					faturacao[j].custo += lista[i]->regCarro.custo;
					break;
				}
			}
			if (j == numDias) { // Nao encontrou uma data, adiciona uma
				strcpy(faturacao[numDias].data, lista[i]->regCarro.dataS);
				faturacao[numDias].custo = lista[i]->regCarro.custo;
				numDias++;
			}
		}
		for (int i = 0; i < numDias; i++) {
			printf("%s %.2f\n", faturacao[i].data, faturacao[i].custo);
		}
}	 else {

		if (!dataValida(dia, mes, ano) || !dataAnterior(dataAnt, data)) {
		printf("invalid date.\n");
		free(nParque);
		return;
		}
		indice = recolheNodesNomData(registos, nParque, data, lista);
		organizaDataS(lista, indice);
		for (int i = 0; i < indice; i++) {
			converteHora(lista[i]->regCarro.horaS, &horaIntS, &minIntS);
			printf("%s %02d:%02d %.2f\n", lista[i]->regCarro.matricula,
				   horaIntS, minIntS, lista[i]->regCarro.custo);
		}
	}
	free(nParque);
}
