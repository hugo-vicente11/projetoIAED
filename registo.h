#ifndef REGISTO_H
#define REGISTO_H
#include "structs.h"

void iniciaV(char *matricula, RegCarroList registos);
void adicionaRegistoNode(RegCarroList *registos, RegCarroNode *registo);
RegCarroNode *obterRegNode(RegCarroList registos, 
						   char matricula[TAMMATRICULA+1], char *nParque);
void iniciaF(char *input, RegCarroList *registos, parkList* parques,
			 char dataAnt[TAMDATA+1]);
#endif // REGISTO_H
