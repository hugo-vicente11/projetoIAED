#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "parque.h"
#include "lib.h"
#include "carros.h"


int main(void) {
	char resposta[BUFSIZ], continua = 1;
    char dataAnt[11] = "00-00-0000";
    char horaAnt[6] = "00:00";
    parkList parques;
    parques.head = NULL;
    parques.tamanho = 0;
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
                iniciaP(resposta, &parques);
                break;

            case 'e':
                iniciaE(resposta, &parques, dataAnt, horaAnt);
                break;
		}
	}
	return 0;
}
