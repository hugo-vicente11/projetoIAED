#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "parque.h"
#include "lib.h"
#include "carros.h"
#include "structs.h"
#include "registo.h"

int main(void) {
	char resposta[BUFSIZ], continua = 1;
    char dataAnt[11] = "00-00-0000", horaAnt[6] = "00:00";
    parkList parques = {NULL, 0};
    RegCarroList registos = {NULL, 0};
	while (continua) {
		fgets(resposta, BUFSIZ, stdin);
		switch (resposta[0]) {
			case 'q':
				// Meter os frees aqui
                continua = 0;
				break;

            case 'p':
                iniciaP(resposta, &parques);
                break;

            case 'e':
                iniciaE(resposta, &parques, dataAnt, horaAnt, &registos);
                break;
            
            case 's':
                iniciaS(resposta, &parques, dataAnt, horaAnt, &registos);
                break;

            case 'v':
                iniciaV(resposta+2, registos);
                break;
            case 'f':
                iniciaF(resposta, &registos, &parques, dataAnt);
                break;
		}
	}
	return 0;
}
