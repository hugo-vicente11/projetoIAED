#include "parque.h"
#include <ctype.h>
#include <string.h>

void iniciaE(char *resposta, Parque parques[], int *lugaresDisp) {
	return;
}


char avaliaCaracteres(char c1, char c2) {
	// Retorna 1 para letras, 2 para numeros e 0 para invalido
	if ((c1 >= 'A' && c1 <= 'Z') &&
		(c2 >= 'A' && 2 <= 'Z'))
			return 1;
	else if (isdigit(c1) && isdigit(c2))
		return 2;
	else
		return 0;
}


// XX-XX-XX
// 01234567
// Um veículo é caracterizado por uma matrícula. Uma matrícula corresponde a uma sequência de 3 pares de caracteres separados pelo carácter '-', sendo que um par apenas pode conter letras maiusculas de 'A' a 'Z' ou apenas pode conter dígitos decimais. Um par não pode ser composto por uma letra e um dígito. Uma matrícula tem que conter sempre pelo menos um par de letras e pelo menos um par de dígitos decimais.
char matriculaValida(char *matricula) {
	int tamanho = strlen(matricula);
	int letras = 0, digitos = 0;
	if (tamanho != 8)
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
