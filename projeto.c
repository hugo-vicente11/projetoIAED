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
    int capMaxima, lugaresDisp;
    float val15, val15a1h, valMaxDia;
} Parque;


typedef struct {
    char *matricula;
    int horaEntrada, minutoEntrada;
    int horaSaida, minutoSaida;
    float custo;
} Carro;


/*
*   Prototipo das funcoes
*/
void formataString(char *str);
int processaInput(char *frase, Parque *parque);
void listaParques(Parque parques[], int nParques);
char saoIguais(const char *str1, const char *str2, int tamanho1, int tamanho2);
char custoInvalido(Parque *parque);
char parqueExiste(Parque parques[], int nParques,char *nome);
void iniciaP(char *resposta, Parque parques[], int *nParques);


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
                iniciaP(resposta, parques, &nParques);
                break;

            case 'e':

                break;

            default:
                printf("Comando invalido.\n");
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
    if (str[j - 1] == ' ' || str[j - 1] == '\n' || str[j - 1] == '\r')
        j--;
    str[j] = '\0';
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
        printf("%s %d %d\n", parques[i].nome, parques[i].capMaxima,
               parques[i].lugaresDisp);
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
            printf("Parque ja existe.\n");
            return;
        }
    }
    
    if (novoParque.capMaxima <= 0) {
        printf("<capacidade>: invalid capacity.\n");
        return;
    }

    if (custoInvalido(&novoParque)) {
        printf("invalid cost.\n");
        return;
    }

    novoParque.lugaresDisp = novoParque.capMaxima;
    parques[*nParques] = novoParque;
    printf("Parque criado com sucesso!!\n");
    (*nParques)++;
    return;
}
