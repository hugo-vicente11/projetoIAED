#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "parque.h"
#include "lib.h"


typedef struct {
    char *matricula;
    int horaEntrada, minutoEntrada;
    int horaSaida, minutoSaida;
    float custo;
} Carro;


/*
*   Prototipo das funcoes
*/

void iniciaE(char *resposta, Parque parques[], int *lugaresDisp);


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
