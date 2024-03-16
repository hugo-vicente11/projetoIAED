#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/*
*   Constantes
*/
#define MAX 20 // Maximo de parques de estacionamento


/*
*   Estruturas
*/
typedef struct {
    char *nome;
    int capMaxima;
    float val15, val15a1h, valMaxDia;
} Parque;


/*
*   Prototipo das funcoes
*/
void formataString(char *str);
int processaInput(char *frase, Parque *parque);
void listaParques(Parque parques[], int nParques);
char saoIguais(const char *str1, const char *str2, int tamanho1, int tamanho2);


int main(void) {
	char resposta[BUFSIZ], continua = 1;
    int nParques = 0; // Numero de parques de estacionamento
    Parque parques[MAX];
	while (continua) {
		fgets(resposta, BUFSIZ, stdin);
		formataString(resposta);
		
        char primeiroChar = resposta[0];

		switch (primeiroChar) {
			case 'q':
				// Meter os frees aqui
                continua = 0;
				break;

            case 'p':
                if (strlen(resposta) == 1) {
                    listaParques(parques, nParques);
                    break;
                }

                if (nParques >= MAX) {
                    printf("too many parks.\n");
                    break;
                }

                Parque novoParque;
                if (processaInput(resposta + 2, &novoParque) != 5) {
                    printf("Erro ao ler os valores.\n");
                    break;
                }

                if (nParques != 0) {
                    int tamanho = strlen(novoParque.nome);
                    char parqueExiste = 0;
                    for (int i = 0; i <= nParques; i++) {
                        if (saoIguais(parques[i].nome, novoParque.nome, 
                            tamanho, strlen(parques[i].nome))) {
                            printf("Parque ja existe.\n");
                            parqueExiste = 1;
                            break;
                        }
                    }
                    if (parqueExiste)
                        break;
                }
                
                if (novoParque.capMaxima <= 0) {
                    printf("<capacidade>: invalid capacity.\n");
                    break;
                }

                if (novoParque.val15 < 0 || novoParque.val15a1h < 0 ||
                    novoParque.valMaxDia < 0 ||
                    !((novoParque.val15 < novoParque.val15a1h) &&
                    (novoParque.val15a1h < novoParque.valMaxDia))) {
                    printf("invalid cost.\n");
                    break;
                }

                parques[nParques] = novoParque;
                printf("Parque criado com sucesso!!\n");
                nParques++;
                break;
            
            case 'e':

                break;
		}
	}

	return 0;
}


/*
*   Declaracao de funcoes
*/


// Retira white space desnecessario (antes, "dentro" e depois do conteudo)
void formataString(char *str) {
    // Remove espacos desnecessarios
    int i, j;

    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i]) ||
            (i > 0 && !isspace((unsigned char)str[i - 1]))) {
            str[j++] = str[i];
        }
    }

    // Adiciona null terminator
    str[--j] = '\0';
}


int processaInput(char *frase, Parque *parque) {
    char aspas = 0;
    char temp[50];
    int resultado;
    for (int i = 0; frase[i] != '\0'; i++) {
        if (frase[i] == '"') {
            aspas = 1;
            break;
        }
    }

    if (aspas) {
        resultado = sscanf(frase, "\"%49[^\"]\" %d %f %f %f",temp, 
                           &parque->capMaxima,&parque->val15, 
                           &parque->val15a1h, &parque->valMaxDia);
    } else {
        resultado = sscanf(frase, "%49[^ ] %d %f %f %f", temp, 
                           &parque->capMaxima, &parque->val15, 
                           &parque->val15a1h, &parque->valMaxDia);
    }
    formataString(temp);
    parque->nome = malloc((strlen(temp) + 1) * sizeof(char));
    strcpy(parque->nome, temp);
    return resultado;
}


void listaParques(Parque parques[], int nParques) {
    for (int i = 0; i < nParques; i++) {
        printf("%s %d %.2f %.2f %.2f\n", parques[i].nome, parques[i].capMaxima,
               parques[i].val15, parques[i].val15a1h, parques[i].valMaxDia);
    }
}


char saoIguais(const char *str1, const char *str2, int tamanho1, int tamanho2) {
    // Se os tamanhos forem diferentes, elas não podem ser iguais
    if (tamanho1 != tamanho2) {
        return 0;
    }

    // Comparando os caracteres
    for (int i = 0; i < tamanho1; i++) {
        if (str1[i] != str2[i]) {
            return 0;
        }
    }
    return 1;
}
