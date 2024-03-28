#ifndef CARROS_H
#define CARROS_H
#include "structs.h"


void iniciaE(char *resposta, parkList *parques, char dataAnt[TAMDATA+1], 
			 char horaAnt[TAMHORA+1]);
char matriculaValida(char *matricula);
char avaliaCaracteres(char c1, char c2);
void converteData(char *data, int *dia, int *mes, int *ano);
void converteHora(char *hora, int *horaInt, int *minutoInt);
char dataValida(int dia, int mes, int ano);
char horaValida(int hora, int minuto);
char dataAnterior(char dataAnt[TAMDATA+1], char horaAnt[TAMHORA+1], 
				  char data[TAMDATA+1], char hora[TAMHORA+1]);
char * processaInputE(char *frase, char matricula[TAMMATRICULA+1],
				   char data[TAMDATA+1], char hora[TAMHORA+1]);
char * processaInputS(char *frase, char matricula[TAMMATRICULA+1],
				   char data[TAMDATA+1], char hora[TAMHORA+1]);
float calculaCusto(float val15, float val15a1h, float valMaxDia, 
					char dataE[TAMDATA+1], char horaE[TAMHORA+1], 
					int diaS, int mesS, int anoS, int horaIntS, int minutoIntS);
void iniciaS(char *resposta, parkList *parques, char dataAnt[TAMDATA+1], 
			 char horaAnt[TAMHORA+1]);
int calculaMinutos(int diaE, int mesE, int anoE, int horaIntE, int minutoIntE,
				   int diaS, int mesS, int anoS, int horaIntS, int minutoIntS);
#endif