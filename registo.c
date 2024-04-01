#include "registo.h"
#include "structs.h"
#include "lib.h"
#include "parque.h"
#include "carros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Adiciona um novo nó de registo de carro à lista de registos.
 * 
 * Esta função adiciona um novo nó de registo de carro ao final da lista 
 * de registos. Se a lista estiver vazia, o novo nó se torna a cabeça da 
 * lista. O tamanho da lista é incrementado após a adição do novo nó.
 * 
 * @param registos Ponteiro para a lista de registos de carros.
 * @param registo Ponteiro para o registo de carro a ser adicionado à lista.
 */
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


/**
 * @brief Obtém um nó de registo de carro com base na matrícula e no nome.
 * 
 * Esta função percorre a lista de registos de carros e retorna o nó de registo 
 * que corresponde à matrícula e ao nome do parque fornecidos. Se o registo não 
 * for encontrado, retorna NULL.
 * 
 * @param registos Lista de registos de carros a serem pesquisados.
 * @param matricula Matrícula do carro a ser encontrado.
 * @param nParque Nome do parque onde o carro está estacionado.
 * @return Retorna um ponteiro para o nó se encontrado, NULL caso contrário.
 */
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


/**
 * @brief Recolhe todos os nós de carro com uma matrícula específica.
 * 
 * Esta função percorre a lista de registos e adiciona todos os nós
 * que correspondem à matrícula fornecida a um array de nós de registo. 
 * Retorna o número de nós recolhidos.
 * 
 * @param registos Ponteiro para a lista de registos de carros.
 * @param matricula Matrícula do carro a ser encontrado.
 * @param lista Array de nós de registo para armazenar os nós recolhidos.
 * @return Retorna o número de nós recolhidos.
 */
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


/**
 * @brief Combina duas sub-listas de carros em uma única lista ordenada.
 * 
 * Esta função recebe um array de nós de registo de carro e três índices que 
 * representam o início, o meio e o fim de duas sub-listas. As sub-listas são 
 * combinadas em uma única lista ordenada pelo nome do parque.
 * 
 * @param lista Array de nós de registo de carro a serem combinados.
 * @param inicio Índice do início da primeira sub-lista.
 * @param meio Índice do fim da primeira lista e início da segunda lista.
 * @param fim Índice do fim da segunda sub-lista.
 */
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


/**
 * @brief Organiza um array de nós de registo de carro por nome de parque.
 * 
 * Esta função utiliza o algoritmo de ordenação merge para organizar 
 * um array de nós de carro por nome do parque. A função é recursiva 
 * e divide o array em duas metades até que cada sub-array contenha apenas um 
 * elemento. Combina os sub-arrays de volta em um único array ordenado.
 * 
 * @param lista Array de nós de registo de carro a serem organizados.
 * @param inicio Índice do início do array ou sub-array.
 * @param fim Índice do fim do array ou sub-array.
 */
void organizaNom(RegCarroNode *lista[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        organizaNom(lista, inicio, meio);
        organizaNom(lista, meio + 1, fim);

        merge(lista, inicio, meio, fim);
    }
}


/**
 * @brief Combina duas sub-listas de carros em uma única lista ordenada.
 * 
 * Esta função recebe um array de nós de registo de carro e três índices que 
 * representam o início, o meio e o fim de duas sub-listas. As sub-listas são 
 * combinadas em uma única lista ordenada pela data e hora de saída do carro. 
 * A função utiliza a função converteData e converteHora para extrair os 
 * componentes da data e hora de saída.
 * 
 * @param lista Array de nós de registo de carro a serem combinados.
 * @param esquerda Índice do início da primeira sub-lista.
 * @param meio Índice do fim da primeira lista e início da segunda lista.
 * @param direita Índice do fim da segunda sub-lista.
 */
void mergeDataS(RegCarroNode *lista[], int esquerda, int meio, int direita) {
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    RegCarroNode *L[n1], *R[n2];

    for (i = 0; i < n1; i++)
        L[i] = lista[esquerda + i];
    for (j = 0; j < n2; j++)
        R[j] = lista[meio + 1 + j];

    i = 0;
    j = 0;
    k = esquerda;

    int anoI, mesI, diaI, horaI, minI, anoJ, mesJ, diaJ, horaJ, minJ;

    while (i < n1 && j < n2) {
        converteData(L[i]->regCarro.dataS, &anoI, &mesI, &diaI);
        converteHora(L[i]->regCarro.horaS, &horaI, &minI);
        converteData(R[j]->regCarro.dataS, &anoJ, &mesJ, &diaJ);
        converteHora(R[j]->regCarro.horaS, &horaJ, &minJ);

        if (anoI < anoJ || (anoI == anoJ && mesI < mesJ) || 
            (anoI == anoJ && mesI == mesJ && diaI < diaJ) ||
            (anoI == anoJ && mesI == mesJ && diaI == diaJ && horaI < horaJ) ||
            (anoI == anoJ && mesI == mesJ && diaI == diaJ && 
            horaI == horaJ && minI < minJ)) {
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


/**
 * @brief Organiza um array de nós de registo de carro por data de saída.
 * 
 * Esta função utiliza o algoritmo de ordenação por mesclagem para organizar 
 * um array de nós de registo de carro por data de saída. A função é recursiva 
 * e divide o array em duas metades até que cada sub-array contenha apenas um 
 * elemento. Em seguida, combina os arrays de volta em um único array ordenado.
 * 
 * @param lista Array de nós de registo de carro a serem organizados.
 * @param esquerda Índice do início do array ou sub-array.
 * @param direita Índice do fim do array ou sub-array.
 */
void mergeSortDataS(RegCarroNode *lista[], int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSortDataS(lista, esquerda, meio);
        mergeSortDataS(lista, meio + 1, direita);

        mergeDataS(lista, esquerda, meio, direita);
    }
}


/**
 * @brief Organiza um array de nós de registo de carro por data de saída.
 * 
 * Esta função recebe um array de nós de registo de carro e o seu tamanho. 
 * Chama a função mergeSortDataS para organizar o array por data de saída.
 * 
 * @param lista Array de nós de registo de carro a serem organizados.
 * @param tamanho Número de nós no array.
 */
void organizaDataS(RegCarroNode *lista[], int tamanho) {
    mergeSortDataS(lista, 0, tamanho - 1);
}


/**
 * @brief Organiza um array de nós de carro por data e hora de entrada.
 * 
 * Esta função recebe um array de nós de registo de carro e o seu tamanho. 
 * Utiliza o algoritmo de ordenação por bolha para organizar o array por data 
 * e hora de entrada. A função converteData e converteHora são usadas para 
 * extrair os componentes da data e hora de entrada.
 * 
 * @param lista Array de nós de registo de carro a serem organizados.
 * @param tamanho Número de nós no array.
 */
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
				(anoI == anoJ && mesI == mesJ && diaI == diaJ && horaI > horaJ)
				||(anoI == anoJ && mesI == mesJ && diaI == diaJ && 
				horaI == horaJ && minI > minJ)) {
				temp = lista[i];
				lista[i] = lista[j];
				lista[j] = temp;
			}
		}
	}
}


/**
 * @brief Inicia a visualização dos registos de um carro específico.
 * 
 * Esta função inicia a visualização dos registos de um carro com uma 
 * matrícula específica. Primeiro, verifica se a matrícula é válida. Em 
 * seguida, recolhe todos os nós de registo que correspondem à matrícula 
 * em um array. O array é organizado por nome de parque e os registos são 
 * impressos na saída padrão.
 * 
 * @param matricula Matrícula do carro cujos registos devem ser visualizados.
 * @param registos Lista de registos de carros a serem pesquisados.
 */
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


/**
 * @brief Extrai os argumentos de uma string de entrada para a função 'f'.
 * 
 * Esta função extrai o nome do parque e a data de uma string de entrada 
 * para a função 'f'. Se a string de entrada contém aspas, o nome do parque 
 * pode conter espaços. Caso contrário, o nome do parque é a primeira palavra 
 * após 'f' e a data é a segunda palavra.
 * 
 * @param input String de entrada contendo a função 'f' e seus argumentos.
 * @param nParque String para armazenar o nome do parque extraído.
 * @param data String para armazenar a data extraída.
 */
void extraiArgsF(char *input, char nParque[BUFSIZ], char data[TAMDATA + 1]) {
    int aspas = temAspas(input);
	if (aspas) {
		sscanf(input, "f \"%[^\"]\" %s", nParque, data);
	} else {
		sscanf(input, "f %s %s", nParque, data);
	}
}


/**
 * @brief Recolhe todos os nós de registo de carro de um parque específico.
 * 
 * Esta função percorre a lista de carros e adiciona todos os nós de 
 * registo que correspondem ao nome do parque, a um array de nós de registo. 
 * Retorna o número de nós recolhidos.
 * 
 * @param registos Ponteiro para a lista de registos de carros.
 * @param nParque Nome do parque a ser encontrado.
 * @param lista Array de nós de registo para armazenar os nós recolhidos.
 * @return Retorna o número de nós recolhidos.
 */
int recolheNodesNome(RegCarroList *registos, char *nParque,
					 RegCarroNode *lista[]) {
	int c = 0;
	int tamanho = strlen(nParque);
	RegCarroNode *atual = registos->head;
	while (atual != NULL) {
		if (saoIguais(atual->regCarro.nParque, nParque,
			strlen(atual->regCarro.nParque), tamanho) &&
			!saoIguais(atual->regCarro.dataS, "00-00-0000",
			TAMDATA, TAMDATA)) 
		{
			lista[c] = atual;
			c++;
		}
		atual = atual->next;
	}
	free(atual);
	return c;
}


/**
 * @brief Recolhe todos os nós de carro de um parque em uma data específica.
 * 
 * Esta função percorre a lista de carros e adiciona todos os nós
 * que correspondem ao nome do parque e à data fornecidos a um array de nós 
 * de registo. Apenas os registos com uma data de saída válida são válidos. 
 * Retorna o número de nós recolhidos.
 * 
 * @param registos Ponteiro para a lista de registos de carros.
 * @param nParque Nome do parque a ser encontrado.
 * @param data Data a ser encontrada.
 * @param lista Array de nós de registo para armazenar os nós recolhidos.
 * @return Retorna o número de nós recolhidos.
 */
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


/**
 * @brief Inicia a função 'f' para calcular a faturação de um parque.
 * 
 * Esta função inicia a função 'f' que calcula a faturação de um parque 
 * específico em um dia específico ou em todos os dias. A função extrai 
 * os argumentos da string de entrada e verifica se o parque existe. 
 * Em seguida, recolhe todos os nós de registo que correspondem ao nome 
 * do parque e à data fornecidos e os organiza por data de saída. 
 * Finalmente, calcula a faturação para cada dia e imprime os resultados.
 * 
 * @param input String de entrada contendo a função 'f' e seus argumentos.
 * @param registos Ponteiro para a lista de registos de carros.
 * @param parques Ponteiro para a lista de parques.
 * @param dataAnt Data anterior para validação.
 * @param dataAntS Segunda data anterior para validação.
 */
void iniciaF(char *input, RegCarroList *registos, parkList* parques,
			 char dataAnt[TAMDATA+1], char dataAntS[TAMDATA+1]) {
	char temp[BUFSIZ], data[TAMDATA+1];
	int horaIntS, minIntS, indice, ano, mes, dia;
	RegCarroNode *lista[registos->tamanho];
	strcpy(data, "");
	extraiArgsF(input, temp, data);
	converteData(data, &dia, &mes, &ano);

	if (obterParkNode(*parques, temp) == NULL) {
		printf("%s: no such parking.\n", temp);
		return;
	}

	if (strcmp(data, "") == 0) {
		Faturacao faturacao[registos->tamanho];
		int numDias = 0;
		indice = recolheNodesNome(registos, temp, lista);
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
		if (strcmp(dataAnt, data) != 0 && strcmp(dataAntS, data) != 0) {
			if (!dataValida(dia, mes, ano) || (!dataAnterior(dataAnt, data) &&
				!dataAnterior(dataAntS, data))) {
				printf("invalid date.\n");
				return;
		}
		}
		indice = recolheNodesNomData(registos, temp, data, lista);
		organizaDataS(lista, indice);
		for (int i = 0; i < indice; i++) {
			converteHora(lista[i]->regCarro.horaS, &horaIntS, &minIntS);
			printf("%s %02d:%02d %.2f\n", lista[i]->regCarro.matricula,
				   horaIntS, minIntS, lista[i]->regCarro.custo);
		}
	}
}

