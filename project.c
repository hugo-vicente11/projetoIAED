// ist1109389 - Hugo Oliveira Vicente
// Projeto - IAED

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
	char resposta[BUFSIZ], dataAnt[11] = "00-00-0000", horaAnt[6] = "00:00";
    char dataAntS[11] = "00-00-0000";
    parkList parques = {NULL, 0};
    RegCarroList registos = {NULL, 0};
	while (1) {
		fgets(resposta, BUFSIZ, stdin);
		switch (resposta[0]) {
			case 'q':
				return 0;
            case 'p':
                iniciaP(resposta, &parques);
                break;
            case 'e':
                iniciaE(resposta, &parques, dataAnt, horaAnt, &registos);
                break;
            case 's':
                iniciaS(resposta, &parques, dataAnt, horaAnt, &registos,
                dataAntS);
                break;
            case 'v':
                iniciaV(resposta+2, registos);
                break;
            case 'f':
                iniciaF(resposta, &registos, &parques, dataAnt, dataAntS);
                break;
            case 'r':
                iniciaR(resposta, &registos, &parques);
                break;
		}
	}
	return 0;
}
