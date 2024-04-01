#include "parque.h"
#include "lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/**
 * @brief Verifica se uma frase contém aspas.
 * 
 * Esta função percorre cada caractere da frase fornecida e verifica se 
 * existe o caractere de aspas (").
 * 
 * @param frase Ponteiro para a frase a ser verificada.
 * @return Retorna 1 se a frase contém aspas, 0 caso contrário.
 */
char temAspas(char *frase) {
    for (int i = 0; frase[i] != '\0'; i++) {
        if (frase[i] == '"')
            return 1;
    }
    return 0;
}


/**
 * @brief Verifica se duas strings são iguais.
 * 
 * Esta função compara duas strings de tamanhos fornecidos. Se os tamanhos 
 * forem diferentes, a função retorna 0. Caso contrário, compara cada 
 * caractere das strings.
 * 
 * @param str1 Primeira string para comparação.
 * @param str2 Segunda string para comparação.
 * @param tamanho1 Tamanho da primeira string.
 * @param tamanho2 Tamanho da segunda string.
 * @return Retorna 1 se as strings forem iguais, 0 caso contrário.
 */
char saoIguais(const char *str1, const char *str2, int tamanho1,
               int tamanho2) {
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
