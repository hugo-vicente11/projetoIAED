#include "parque.h"
#include "lib.h"
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


char temAspas(char *frase) {
    for (int i = 0; frase[i] != '\0'; i++) {
        if (frase[i] == '"')
            return 1;
    }
    return 0;
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
