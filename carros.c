#include "carros.h"
#include "parque.h"
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include <ctype.h>
#include <string.h>
#include "registo.h"


char * processaInputE(char *frase, char matricula[TAMMATRICULA+1],
				   char data[TAMDATA+1], char hora[TAMHORA+1]) {
    char temp[BUFSIZ];

    if (temAspas(frase)) {
        sscanf(frase, "e \"%8191[^\"]\" %8s %s %s", temp, matricula, data, hora);
    } else {
        sscanf(frase, "e %8191[^ ] %8s %s %s", temp, matricula, data, hora);
    }
    char *nome = (char*)malloc((strlen(temp) + 1));
    strcpy(nome, temp);
    return nome;
}


char * processaInputS(char *frase, char matricula[TAMMATRICULA+1],
				   char data[TAMDATA+1], char hora[TAMHORA+1]) {
    char temp[BUFSIZ];

    if (temAspas(frase)) {
        sscanf(frase, "s \"%8191[^\"]\" %8s %s %s", temp, matricula, data, hora);
    } else {
        sscanf(frase, "s %8191[^ ] %8s %s %s", temp, matricula, data, hora);
    }
    char *nome = (char*)malloc((strlen(temp) + 1));
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
	int letras = 0, digitos = 0;
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


char dataAnterior(char dataAnt[TAMDATA+1], char horaAnt[TAMHORA+1],
				  char data[TAMDATA+1], char hora[TAMHORA+1]) {
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
				   char data[TAMDATA+1], char hora[TAMHORA+1]) {
	CarroNode *novoCarro = (CarroNode*)malloc(sizeof(CarroNode));
	strcpy(novoCarro->carro.matricula, matricula);
	strcpy(novoCarro->carro.dataEntrada, data);
	strcpy(novoCarro->carro.horaEntrada, hora);
	novoCarro->next = parque->carros.head;
	parque->carros.head = novoCarro;
	parque->carros.tamanho++;
	parque->lugaresDisp--;
	return;
}

void removeCarro(Parque *parque, char matricula[TAMMATRICULA+1]) {
	CarroNode *atual = parque->carros.head;
	CarroNode *anterior = NULL;
	while (atual != NULL) {
		if (saoIguais(atual->carro.matricula, matricula, 
					   TAMMATRICULA, TAMMATRICULA)) {
			if (anterior == NULL) {
				parque->carros.head = atual->next;
			} else {
				anterior->next = atual->next;
			}
			// printf("%s ", atual->carro.matricula);
			free(atual);
			parque->carros.tamanho--;
			parque->lugaresDisp++;
			return;
		}
		anterior = atual;
		atual = atual->next;
	}
	return;
}


// Funcao que verifica se um carro com a matricula inserida ja existe em um parque
CarroNode * obtemCarro(parkList parques, char matricula[TAMMATRICULA+1]) {
	parkNode *atual = parques.head;
	while (atual != NULL) {
		CarroNode *atualCarro = atual->parque.carros.head;
		while (atualCarro != NULL) {
			if (saoIguais(atualCarro->carro.matricula, matricula, 
						   TAMMATRICULA, TAMMATRICULA))
				return atualCarro;
			atualCarro = atualCarro->next;
		}
		atual = atual->next;
	}
	return NULL;
}


void iniciaE(char *resposta, parkList *parques, char dataAnt[TAMDATA+1], 
			 char horaAnt[TAMHORA+1], RegCarroList *registos) {
	char matricula[TAMMATRICULA+1], data[TAMDATA+1], hora[TAMHORA+1];
	int dia, mes, ano;
	int horaInt, minutoInt;
	parkNode *parkEscolhido = (parkNode*)malloc(sizeof(parkNode));
	char *nome = processaInputE(resposta, matricula, data, hora);
	parkEscolhido = obterParkNode(*parques, nome);

	if (parkEscolhido == NULL) {
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

    if (obtemCarro(*parques, matricula) != NULL){
        printf("%s: invalid vehicle entry.\n", matricula);
        return;
    }

	RegCarroNode *novoReg = (RegCarroNode*)malloc(sizeof(RegCarroNode));
	strcpy(novoReg->regCarro.matricula, matricula);
	novoReg->regCarro.nParque = malloc((strlen(nome) + 1));
	strcpy(novoReg->regCarro.nParque, nome);
	strcpy(novoReg->regCarro.dataE, data);
	strcpy(novoReg->regCarro.horaE, hora);
	strcpy(novoReg->regCarro.dataS, "00-00-0000");
	strcpy(novoReg->regCarro.horaS, "00:00");
	novoReg->regCarro.custo = 0;
	novoReg->next = NULL;
adicionaRegistoNode(registos, novoReg);
	adicionaCarro(&parkEscolhido->parque, matricula, data, hora);

	printf("%s %d\n", parkEscolhido->parque.nome,
		   parkEscolhido->parque.lugaresDisp);

	strcpy(dataAnt, data);
	strcpy(horaAnt, hora);

	return;
}


float calculaCusto(float val15, float val15a1h, float valMaxDia, 
                    char dataE[TAMDATA+1], char horaE[TAMHORA+1], 
                    int diaS, int mesS, int anoS, int horaIntS, 
					int minutoIntS) {
    int diaE, mesE, anoE, horaIntE, minutoIntE;
    long long minutos = 0, particoes = 0;
    float custo = 0;
    converteData(dataE, &diaE, &mesE, &anoE);
    converteHora(horaE, &horaIntE, &minutoIntE);
    minutos += calculaMinutos(anoS, mesS, diaS, horaIntS, minutoIntS);
	minutos -= calculaMinutos(anoE, mesE, diaE, horaIntE, minutoIntE);
    if (minutos % 15 == 0) {
        particoes = minutos / 15;
	}
    else {
        particoes = minutos / 15 + 1;
	}
	calculaRecursivaMins(val15, val15a1h, valMaxDia, particoes, &custo);
    return custo;
}


void calculaRecursivaMins(float val15, float val15a1h, float valMaxDia,
						  long long particoes, float *custo) {
	if (particoes <= 4) {
		float adicionar = particoes * val15;
		if (adicionar > valMaxDia){
			adicionar = valMaxDia;
		}
		*custo += adicionar;
		return;
	} else if (particoes > 4 && particoes <= 96) {
		float adicionar = (4 * val15) + ((particoes - 4) * val15a1h);
		if (adicionar > valMaxDia){
			adicionar = valMaxDia;
		}
		*custo += adicionar;
		return;
	} else if (particoes > 96) {
		*custo += valMaxDia;
		particoes -= 96;
		calculaRecursivaMins(val15, val15a1h, valMaxDia, particoes, custo);
	}
}


// Funcao que calcula o numero de minutos entre duas datas
long long calculaMinutos(int ano, int mes, int dia, int hora, int minuto) {
    long long total_minutos = 0;
    int dias_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    total_minutos += ano * 525600;
    for (int i = 0; i < mes - 1; i++) {
        total_minutos += 1440 * dias_mes[i];
    }
    total_minutos += 1440 * dia;
    total_minutos += 60 * hora;
    total_minutos += minuto;
    return total_minutos;
}


void iniciaS(char *resposta, parkList *parques, char dataAnt[TAMDATA+1], 
			char horaAnt[TAMHORA+1], RegCarroList *registos) {
	char matricula[TAMMATRICULA+1], data[TAMDATA+1], hora[TAMHORA+1];
	int dia, mes, ano;
	int horaInt, minutoInt;
	int horaIntE, minutoIntE;
	float custo;
	CarroNode *carroEscolhido = (CarroNode*)malloc(sizeof(CarroNode));
	parkNode *parkEscolhido = (parkNode*)malloc(sizeof(parkNode));
	char *nome = processaInputS(resposta, matricula, data, hora);
	parkEscolhido = obterParkNode(*parques, nome);
	carroEscolhido = obtemCarro(*parques, matricula);
	
	converteData(data, &dia, &mes, &ano);
	converteHora(hora, &horaInt, &minutoInt);
	if (parkEscolhido == NULL) {
		printf("%s: no such parking.\n", nome);
		return;
	}

	if (!matriculaValida(matricula)) {
		printf("%s: invalid licence plate.\n", matricula);
		return;
	}

	if (carroEscolhido == NULL){
		printf("%s: invalid vehicle exit.\n", matricula);
		return;
	}

	if (!dataValida(dia, mes, ano)) {
		printf("invalid date.\n");
		return;
	}

	if (!horaValida(horaInt, minutoInt)) {
		printf("invalid date.\n");
		return;
	}
	
	if (dataAnterior(dataAnt, horaAnt, data, hora)) {
		printf("invalid date.\n");
		return;
	}

	converteHora(carroEscolhido->carro.horaEntrada, &horaIntE, &minutoIntE);
	custo = calculaCusto(parkEscolhido->parque.val15, parkEscolhido->parque.val15a1h, 
						 parkEscolhido->parque.valMaxDia, carroEscolhido->carro.dataEntrada, 
						 carroEscolhido->carro.horaEntrada, dia, mes, ano, horaInt, minutoInt);
	printf("%s %s %02d:%02d %s %02d:%02d %.2f\n", matricula, carroEscolhido->carro.dataEntrada, 
		   horaIntE, minutoIntE, data, horaInt, minutoInt, custo);
	RegCarroNode *reg = obterRegNode(*registos, matricula, nome);
	strcpy(reg->regCarro.dataS, data);
	strcpy(reg->regCarro.horaS, hora);
	reg->regCarro.custo = custo;
	removeCarro(&parkEscolhido->parque, matricula);
	
}
