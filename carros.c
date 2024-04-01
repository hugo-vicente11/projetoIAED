#include "carros.h"
#include "parque.h"
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include <ctype.h>
#include <string.h>
#include "registo.h"

/**
 * @brief Processa a entrada do usuário para o comando 'e'.
 * 
 * Esta função lê a frase de entrada do usuário, extrai a matrícula do carro, 
 * a data e a hora, e retorna o nome do parque.
 * 
 * @param frase Ponteiro para a frase de entrada do usuário.
 * @param matricula Array de caracteres onde a matrícula do carro é guardada.
 * @param data Array de caracteres onde a data será armazenada.
 * @param hora Array de caracteres onde a hora será armazenada.
 * @return Ponteiro para o nome do parque.
 */
void processaInputE(char *frase, char temp[BUFSIZ],
 char matricula[TAMMATRICULA+1], char data[TAMDATA+1], char hora[TAMHORA+1]) {
    if (temAspas(frase)) {
        sscanf(frase, "e \"%8191[^\"]\" %8s %s %s", temp, matricula, data,
			   hora);
    } else {
        sscanf(frase, "e %8191[^ ] %8s %s %s", temp, matricula, data, hora);
    }
	return;
}


/**
 * @brief Processa a entrada do usuário para o comando 's'.
 * 
 * Esta função lê a frase de entrada do usuário, extrai a matrícula do carro, 
 * a data e a hora, e retorna o nome do parque.
 * 
 * @param frase Ponteiro para a frase de entrada do usuário.
 * @param matricula Array de caracteres onde a matrícula do carro é guardada.
 * @param data Array de caracteres onde a data será armazenada.
 * @param hora Array de caracteres onde a hora será armazenada.
 * @return Ponteiro para o nome do parque.
 */
void processaInputS(char *frase, char temp[BUFSIZ],
					  char matricula[TAMMATRICULA+1],char data[TAMDATA+1],
					char hora[TAMHORA+1]) {
	if (temAspas(frase)) {
        sscanf(frase, "s \"%8191[^\"]\" %8s %s %s", temp, matricula, data,
			   hora);
    } else {
        sscanf(frase, "s %8191[^ ] %8s %s %s", temp, matricula, data, hora);
    }
    return;
}
	

/**
 * @brief Avalia se os caracteres são letras ou números.
 * 
 * Esta função recebe dois caracteres e retorna 1 se ambos são letras,
 * 2 se ambos são números, e 0 se são inválidos.
 * 
 * @param c1 Primeiro caractere para avaliação.
 * @param c2 Segundo caractere para avaliação.
 * @return Retorna 1 para letras, 2 para números e 0 para inválido.
 */
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


/**
 * @brief Verifica se uma matrícula é válida.
 * 
 * Esta função verifica se a matrícula fornecida segue o formato correto,
 * que é LL-NN-LL ou NN-LL-NN, onde L é uma letra e N é um número.
 * 
 * @param matricula Ponteiro para a matrícula a ser verificada.
 * @return Retorna 1 se a matrícula for válida, 0 caso contrário.
 */
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


/**
 * @brief Converte uma data de string para inteiros.
 * 
 * Esta função recebe uma data no formato DD-MM-AAAA como string e 
 * converte para inteiros separados para dia, mês e ano.
 * 
 * @param data Ponteiro para a data em formato de string.
 * @param dia Ponteiro para o dia convertido.
 * @param mes Ponteiro para o mês convertido.
 * @param ano Ponteiro para o ano convertido.
 */
void converteData(char *data, int *dia, int *mes, int *ano) {
	*dia = (data[0] - '0') * 10 + (data[1] - '0');
	*mes = (data[3] - '0') * 10 + (data[4] - '0');
	*ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + 
		   (data[8] - '0') * 10 + (data[9] - '0');
	return;
}


/**
 * @brief Converte uma hora de string para inteiros.
 * 
 * Esta função recebe uma hora no formato HH:MM como string e 
 * converte para inteiros separados para hora e minuto.
 * 
 * @param hora Ponteiro para a hora em formato de string.
 * @param horaInt Ponteiro para a hora convertida.
 * @param minutoInt Ponteiro para o minuto convertido.
 */
void converteHora(char *hora, int *horaInt, int *minutoInt) {
	if (strlen(hora) == 5) {
		*horaInt = (hora[0] - '0') * 10 + (hora[1] - '0');
		*minutoInt = (hora[3] - '0') * 10 + (hora[4] - '0');
	} else {
		*horaInt = (hora[0] - '0');
		*minutoInt = (hora[2] - '0') * 10 + (hora[3] - '0');
	}
}


/**
 * @brief Verifica se uma data é válida.
 * 
 * Esta função verifica se o dia, mês e ano fornecidos formam uma data válida.
 * 
 * @param dia Dia a ser verificado.
 * @param mes Mês a ser verificado.
 * @param ano Ano a ser verificado.
 * @return Retorna 1 se a data for válida, 0 caso contrário.
 */
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


/**
 * @brief Verifica se uma hora é válida.
 * 
 * Esta função verifica se a hora e o minuto fornecidos formam uma hora válida.
 * 
 * @param hora Hora a ser verificada.
 * @param minuto Minuto a ser verificado.
 * @return Retorna 1 se a hora for válida, 0 caso contrário.
 */
char horaValida(int hora, int minuto) {
	if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59)
		return 0;
	return 1;
}


/**
 * @brief Verifica se uma data e hora são anteriores a outra.
 * 
 * Esta função recebe duas datas e horas e verifica se a primeira é anterior
 * à segunda. As datas e horas são fornecidas como strings.
 * 
 * @param dataAnt Data anterior a ser verificada.
 * @param horaAnt Hora anterior a ser verificada.
 * @param data Data a ser comparada.
 * @param hora Hora a ser comparada.
 * @return Retorna 1 se a data e hora ANT forem anteriores, 0 caso contrário.
 */
char dataHAnterior(char dataAnt[TAMDATA+1], char horaAnt[TAMHORA+1],
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


/**
 * @brief Verifica se uma data é anterior a outra.
 * 
 * Esta função recebe duas datas como strings e verifica se a primeira é 
 * anterior à segunda.
 * 
 * @param dataAnt Data anterior a ser verificada.
 * @param data Data a ser comparada.
 * @return Retorna 1 se a data anterior for anterior, 0 caso contrário.
 */
char dataAnterior(char dataAnt[TAMDATA+1], char data[TAMDATA+1]) {
	int diaAnt, mesAnt, anoAnt;
	int dia, mes, ano;
	converteData(dataAnt, &diaAnt, &mesAnt, &anoAnt);
	converteData(data, &dia, &mes, &ano);
	if (anoAnt > ano)
		return 1;
	else if (anoAnt == ano) {
		if (mesAnt > mes)
			return 1;
		else if (mesAnt == mes) {
			if (diaAnt > dia)
				return 1;
		}
	}
	return 0;
}


/**
 * @brief Adiciona um carro ao parque.
 * 
 * Esta função cria um novo carro com a matrícula, data e hora fornecidas, 
 * e adiciona-o à lista de carros do parque.
 * 
 * @param parque Ponteiro para o parque onde o carro será adicionado.
 * @param matricula Matrícula do carro a ser adicionado.
 * @param data Data de entrada do carro.
 * @param hora Hora de entrada do carro.
 */
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


/**
 * @brief Remove um carro do parque.
 * 
 * Esta função remove um carro do parque com base na matrícula fornecida.
 * 
 * @param parque Ponteiro para o parque de onde o carro será removido.
 * @param matricula Matrícula do carro a ser removido.
 */
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


/**
 * @brief Obtém um carro de um parque com base na matrícula.
 * 
 * Esta função percorre a lista de parques e seus carros para encontrar
 * um carro com a matrícula fornecida.
 * 
 * @param parques Lista de parques a serem pesquisados.
 * @param matricula Matrícula do carro a ser encontrado.
 * @return Retorna um ponteiro para o carro se encontrado, NULL caso contrário.
 */
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


/**
 * @brief Processa a entrada de um carro em um parque.
 * 
 * Esta função recebe a resposta do usuário, a lista de parques, a data e hora 
 * anteriores e a lista de registos. Processa a entrada de um carro no parque 
 * escolhido, atualizando as informações necessárias.
 * 
 * @param resposta Resposta do usuário.
 * @param parques Lista de parques.
 * @param dataAnt Data anterior.
 * @param horaAnt Hora anterior.
 * @param registos Lista de registos de carros.
 */
void iniciaE(char *resposta, parkList *parques, char dataAnt[TAMDATA+1], 
			 char horaAnt[TAMHORA+1], RegCarroList *registos) {
	char matricula[TAMMATRICULA+1], data[TAMDATA+1], hora[TAMHORA+1];
	char nome[BUFSIZ];
	int dia, mes, ano;
	int horaInt, minutoInt;
	processaInputE(resposta, nome, matricula, data, hora);
	parkNode *parkEscolhido = obterParkNode(*parques, nome);

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

	if (dataHAnterior(dataAnt, horaAnt, data, hora)) {
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


/**
 * @brief Calcula o custo de estacionamento de um carro.
 * 
 * Esta função calcula o custo com base na data e hora de entrada e saída do 
 * carro. O custo é calculado em blocos de 15 minutos.
 * 
 * @param val15 Custo para os primeiros 15 minutos.
 * @param val15a1h Custo para os próximos 45 minutos.
 * @param valMaxDia Custo máximo por dia.
 * @param dataE Data de entrada do carro.
 * @param horaE Hora de entrada do carro.
 * @param diaS Dia de saída do carro.
 * @param mesS Mês de saída do carro.
 * @param anoS Ano de saída do carro.
 * @param horaIntS Hora de saída do carro.
 * @param minutoIntS Minuto de saída do carro.
 * @return Retorna o custo calculado.
 */
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


/**
 * @brief Calcula o custo do estacionamento de forma recursiva.
 * 
 * Esta função calcula o custo do estacionamento com base no número de 
 * partições de 15 minutos. O custo é calculado de forma recursiva para 
 * cada dia de estacionamento.
 * 
 * @param val15 Custo para os primeiros 15 minutos.
 * @param val15a1h Custo para os próximos 45 minutos.
 * @param valMaxDia Custo máximo por dia.
 * @param particoes Número de partições de 15 minutos.
 * @param custo Ponteiro para o custo total acumulado.
 */
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


/**
 * @brief Calcula o total de minutos desde o início do tempo.
 * 
 * Esta função calcula o total de minutos desde o início do tempo (assumindo 
 * o ano 0) até a data e hora fornecidas.
 * 
 * @param ano Ano da data.
 * @param mes Mês da data.
 * @param dia Dia da data.
 * @param hora Hora do dia.
 * @param minuto Minuto da hora.
 * @return Retorna o total de minutos calculado.
 */
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


/**
 * @brief Inicia o processo de saída de um carro de um parque.
 * 
 * Esta função processa a saída de um carro de um parque. Ela verifica a 
 * validade da matrícula, data e hora, calcula o custo do estacionamento, 
 * atualiza os registos e remove o carro do parque.
 * 
 * @param resposta Resposta do usuário.
 * @param parques Lista de parques.
 * @param dataAnt Data anterior.
 * @param horaAnt Hora anterior.
 * @param registos Lista de registos de carros.
 * @param dataAntS Data anterior de saída.
 */
void iniciaS(char *resposta, parkList *parques, char dataAnt[TAMDATA+1], 
			char horaAnt[TAMHORA+1], RegCarroList *registos, 
			char dataAntS[TAMDATA+1]) {
	char matricula[TAMMATRICULA+1], data[TAMDATA+1], hora[TAMHORA+1];
	char nome[BUFSIZ];
	int dia, mes, ano;
	int horaInt, minutoInt;
	int horaIntE, minutoIntE;
	float custo;
	CarroNode *carroEscolhido;
	parkNode *parkEscolhido;
	processaInputS(resposta, nome, matricula, data, hora);
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
	
	if (dataHAnterior(dataAnt, horaAnt, data, hora)) {
		printf("invalid date.\n");
		return;
	}

	converteHora(carroEscolhido->carro.horaEntrada, &horaIntE, &minutoIntE);
	custo = calculaCusto(parkEscolhido->parque.val15, 
						 parkEscolhido->parque.val15a1h, 
						 parkEscolhido->parque.valMaxDia,
						 carroEscolhido->carro.dataEntrada, 
						 carroEscolhido->carro.horaEntrada, dia, mes, ano,
						 horaInt, minutoInt);
	printf("%s %s %02d:%02d %s %02d:%02d %.2f\n", matricula, 
		   carroEscolhido->carro.dataEntrada, 
		   horaIntE, minutoIntE, data, horaInt, minutoInt, custo);
	RegCarroNode *reg = obterRegNode(*registos, matricula, nome);
	strcpy(reg->regCarro.dataS, data);
	strcpy(dataAntS, data);
	strcpy(reg->regCarro.horaS, hora);
	reg->regCarro.custo = custo;
	removeCarro(&parkEscolhido->parque, matricula);
}
