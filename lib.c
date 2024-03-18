#include "parque.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// Retira white space desnecessario (antes, "dentro" e depois do conteudo)
void formataString(char *str) {
    // Remove espacos desnecessarios
    int i, j;

    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i]) ||
            (i > 0 && !isspace((unsigned char)str[i - 1]))) {
            str[j++] = str[i];
        }
    }

    // Adiciona null terminator
    if (str[j - 1] == ' ' || str[j - 1] == '\n' || str[j - 1] == '\r')
        j--;
    str[j] = '\0';
}


int processaInput(char *frase, Parque *parque) {
    char aspas = 0;
    char temp[BUFSIZ];
    int resultado;
    for (int i = 0; frase[i] != '\0'; i++) {
        if (frase[i] == '"') {
            aspas = 1;
            break;
        }
    }

    if (aspas) {
        resultado = sscanf(frase, "\"%8191[^\"]\" %d %f %f %f",temp, 
                           &parque->capMaxima,&parque->val15, 
                           &parque->val15a1h, &parque->valMaxDia);
    } else {
        resultado = sscanf(frase, "%8191[^ ] %d %f %f %f", temp, 
                           &parque->capMaxima, &parque->val15, 
                           &parque->val15a1h, &parque->valMaxDia);
    }
    formataString(temp);
    parque->nome = malloc((strlen(temp) + 1) * sizeof(char));
    strcpy(parque->nome, temp);
    return resultado;
}





char saoIguais(const char *str1, const char *str2, int tamanho1, int tamanho2) {
    // Se os tamanhos forem diferentes, elas não podem ser iguais
    if (tamanho1 != tamanho2) {
        return 0;
    }

    // Comparando os caracteres
    for (int i = 0; i < tamanho1; i++) {
        if (str1[i] != str2[i]) {
            return 0;
        }
    }
    return 1;
}
