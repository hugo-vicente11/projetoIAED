#ifndef CARROS_H
#define CARROS_H
#include "structs.h"


void iniciaE(char *resposta, parkList *parques, char dataAnt[11], 
			 char horaAnt[6]);
char matriculaValida(char *matricula);
char avaliaCaracteres(char c1, char c2);
void converteData(char *data, int *dia, int *mes, int *ano);
void converteHora(char *hora, int *horaInt, int *minutoInt);
char dataValida(int dia, int mes, int ano);
char horaValida(int hora, int minuto);
char dataAnterior(char dataAnt[11], char horaAnt[6], char data[11],
                  char hora[6]);


#endif