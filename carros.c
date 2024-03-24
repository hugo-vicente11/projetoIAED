#include "carros.h"
#include "parque.h"
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include <ctype.h>
#include <string.h>


char * processaInputE(char *frase, char matricula[TAMMATRICULA+1],
				   char data[11], char hora[6]) {
	// Passar a frase como frase+2 na function call!!!
    char temp[BUFSIZ];

    if (temAspas(frase)) {
        sscanf(frase, "\"%8191[^\"]\" %8s %s %s", temp, matricula, data, hora);
    } else {
        sscanf(frase, "%8191[^ ] %8s %s %s", temp, matricula, data, hora);
    }
    formataString(temp);
    char *nome = malloc((strlen(temp) + 1) * sizeof(char));
    strcpy(nome, temp);
    return nome;
}
	

char avaliaCaracteres(char c1, char c2) {
	// Retorna 1 para letras, 2 para numeros e 0 para invalido
	if ((c1 >= 'A' && c1 <= 'Z') &&
		(c2 >= 'A' && c2 <= 'Z'))
			return 1;
	else if (isdigit(c1) && isdigit(c2))
		return 2;
	else
		return 0;
}


char matriculaValida(char *matricula) {
	int tamanho = strlen(matricula);
	int letras = 0, digitos = 0;
	if (tamanho != TAMMATRICULA)
		return 0;
	
	if (matricula[2] != '-' || matricula[5] != '-')
		return 0;

	for (int i = 0; i <= 6; i += 3){
		if (avaliaCaracteres(matricula[i], matricula[i+1]) == 0)
			return 0;
		else if (avaliaCaracteres(matricula[i], matricula[i+1]) == 1)
			letras++;
		else
			digitos++;
	}

	if (letras + digitos != 3 || letras == 0 || digitos == 0)
		return 0;

	return 1;
}


void converteData(char *data, int *dia, int *mes, int *ano) {
	*dia = (data[0] - '0') * 10 + (data[1] - '0');
	*mes = (data[3] - '0') * 10 + (data[4] - '0');
	*ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + 
		   (data[8] - '0') * 10 + (data[9] - '0');
	return;
}


void converteHora(char *hora, int *horaInt, int *minutoInt) {
	if (strlen(hora) == 5) {
		*horaInt = (hora[0] - '0') * 10 + (hora[1] - '0');
		*minutoInt = (hora[3] - '0') * 10 + (hora[4] - '0');
	} else {
		*horaInt = (hora[0] - '0');
		*minutoInt = (hora[2] - '0') * 10 + (hora[3] - '0');
	}
}


char dataValida(int dia, int mes, int ano) {
	if (dia < 1 || ano  < 0 || mes < 1 || mes > 12)
		return 0;
	// Fevereiro tem 28 dias 
	if (mes == 2) {
		if (dia > 28)
			return 0;
	}
	// Meses com 30 dias
	else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
		if (dia > 30)
			return 0;
	}
	// Meses com 31 dias
	else if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || 
			   mes == 8 || mes == 10 || mes == 12) {
		if (dia > 31)
			return 0;
	}
	return 1;
}


char horaValida(int hora, int minuto) {
	if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59)
		return 0;
	return 1;
}


char dataAnterior(char dataAnt[11], char horaAnt[6], char data[11],
				  char hora[6]) {
	int diaAnt, mesAnt, anoAnt, horaIntAnt, minutoIntAnt;
	int dia, mes, ano, horaInt, minutoInt;
	converteData(dataAnt, &diaAnt, &mesAnt, &anoAnt);
	converteHora(horaAnt, &horaIntAnt, &minutoIntAnt);
	converteData(data, &dia, &mes, &ano);
	converteHora(hora, &horaInt, &minutoInt);
	if (anoAnt > ano)
		return 1;
	else if (anoAnt == ano) {
		if (mesAnt > mes)
			return 1;
		else if (mesAnt == mes) {
			if (diaAnt > dia)
				return 1;
			else if (diaAnt == dia) {
				if (horaIntAnt > horaInt)
					return 1;
				else if (horaIntAnt == horaInt) {
					if (minutoIntAnt > minutoInt)
						return 1;
				}
			}
		}
	}
	return 0;
}


// Adiciona CarroNode a CarroList de um parque
void adicionaCarro(Parque *parque, char matricula[TAMMATRICULA+1], 
				   char data[11], char hora[6]) {
	CarroNode *novoCarro = malloc(sizeof(CarroNode));
	strcpy(novoCarro->carro.matricula, matricula);
	strcpy(novoCarro->carro.dataEntrada, data);
	strcpy(novoCarro->carro.horaEntrada, hora);
	novoCarro->carro.custo = 0;
	novoCarro->next = parque->carros.head;
	parque->carros.head = novoCarro;
	parque->carros.tamanho++;
	parque->lugaresDisp--;
	return;
}

// Funcao que verifica se um carro com a matricula inserida ja existe em um parque
char carroExiste(parkList parques, char matricula[TAMMATRICULA+1]) {
	parkNode *atual = parques.head;
	while (atual != NULL) {
		CarroNode *atualCarro = atual->parque.carros.head;
		while (atualCarro != NULL) {
			if (saoIguais(atualCarro->carro.matricula, matricula, 
						   strlen(atualCarro->carro.matricula), 
						   TAMMATRICULA))
				return 1;
			atualCarro = atualCarro->next;
		}
		atual = atual->next;
	}
	return 0;
}


void iniciaE(char *resposta, parkList *parques, char dataAnt[11], 
			 char horaAnt[6]) {
	char matricula[TAMMATRICULA+1], data[11], hora[6];
	int dia, mes, ano;
	int horaInt, minutoInt;
	parkNode *parkEscolhido = malloc(sizeof(parkNode));
	char *nome = processaInputE(resposta + 2, matricula, data, hora);
	parkEscolhido = obterParkNode(*parques, nome);

	if (!parqueExiste(*parques, nome)) {
		printf("%s: no such parking.\n", nome);
		return;
	}
	
	if (!matriculaValida(matricula)) {
		printf("%s: invalid licence plate.\n", matricula);
		return;
	}

	if (parkEscolhido->parque.lugaresDisp == 0) {
		printf("%s: parking is full.\n", nome);
		return;
	}

	converteData(data, &dia, &mes, &ano);

	if (!dataValida(dia, mes, ano)) {
		printf("invalid date.\n");
		return;
	}

	converteHora(hora, &horaInt, &minutoInt);

	if (!horaValida(horaInt, minutoInt)) {
		printf("invalid date.\n");
		return;
	}

	// Falta verificar se a data e a hora inserida e anterior a data e hora atual
	if (dataAnterior(dataAnt, horaAnt, data, hora)) {
		printf("invalid date.\n");
		return;
	}

    if (carroExiste(*parques, matricula)) {
        printf("%s: invalid vehicle entry.\n", matricula);
        return;
    }

	adicionaCarro(&parkEscolhido->parque, matricula, data, hora);

	printf("%s %d\n", parkEscolhido->parque.nome, parkEscolhido->parque.lugaresDisp);

	strcpy(dataAnt, data);
	strcpy(horaAnt, hora);

	return;
}
