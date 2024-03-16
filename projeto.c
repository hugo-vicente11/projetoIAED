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
    char nome[100];
    int capMaxima;
    float val15, val15a1h, valMaxDia;
} Parque;


/*
*   Prototipo das funcoes
*/
void formataString(char *str);
int processaInput(char *frase, char *nome, int *capMaxima, float *val15,
                  float *val15a1h, float *valMaxDia);


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
                // p [ <nome-parque> <capacidade> <valor-15> <valor-15-apos-1hora> <valor-max-diario> ]
                // p "CC Colombo" 400 0.25 0.40 20.00

                if (strlen(resposta) == 1) {
                    // Listar todos os parques existentes no sistema
                    printf("Listei!\n");
                    break;
                }

                if (nParques >= MAX) {
                    printf("too many parks.\n");
                    break;
                }

                Parque novoParque;
                if (processaInput(resposta + 2, novoParque.nome, 
                    &novoParque.capMaxima,
                    &novoParque.val15, &novoParque.val15a1h,
                    &novoParque.valMaxDia) != 5) {
                    printf("Erro ao ler os valores.\n");
                    break;
                }

                if (nParques != 0) {
                    char erro = 0;
                    for (int i = 0; i <= nParques; i++) {
                        if (strcmp(parques[i].nome, novoParque.nome) != 0) {
                            erro = 1;
                            break;
                        }
                    }
                    if (erro) {
                        printf("<nome-parque>: parking already exists.\n");
                        break;
                    }
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


int processaInput(char *frase, char *nome, int *capMaxima, float *val15,
                  float *val15a1h, float *valMaxDia) {
    char aspas = 0;
    for (int i = 0; frase[i] != '\0'; i++) {
        if (frase[i] == '"') {
            aspas = 1;
            break;
        }
    }

    if (aspas) {
        return sscanf(frase, "\"%99[^\"]\" %d %f %f %f",nome, capMaxima,
                      val15, val15a1h, valMaxDia);
    } else {
        return sscanf(frase, "%99[^ ] %d %f %f %f", nome, capMaxima,
                      val15, val15a1h, valMaxDia);
    }
}
