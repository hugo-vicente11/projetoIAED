#include "registo.h"
#include "structs.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// RegCarroList hashTable[HASHSIZE]

unsigned hash(char *s) {
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}


// procura: pesquisa s na hashtab e retorna todas as aparências
RegCarroNode *procura(char *s, RegCarroList hashtab[HASHSIZE]) {
    RegCarroNode *np;

    for (np = hashtab[hash(s)].head; np != NULL; np = np->next) {
        if (saoIguais(s, np->regCarro.matricula, TAMMATRICULA, TAMMATRICULA))
            return np;
	}
    return NULL;
}

// Install: insere s na hashtab, e usa seperate chaining
RegCarro *install(RegCarro *regCarro, RegCarroList hashtab[HASHSIZE]) {
	RegCarroNode *np;
	unsigned hashval;

	if ((np = procura(regCarro->matricula, hashtab)) == NULL) {
		np = (RegCarroNode *) malloc(sizeof(*np));
		if (np == NULL || (np->regCarro.matricula = strdup(regCarro->matricula)) == NULL)
			return NULL;
		hashval = hash(regCarro->matricula);
		np->next = hashtab[hashval].head;
		hashtab[hashval].head = np;
		hashtab[hashval].tamanho++;
	} else
		free((void *) np->regCarro.matricula);
	if ((np->regCarro.matricula = strdup(regCarro->matricula)) == NULL)
		return NULL;
	np->regCarro.tipo = regCarro->tipo;
	strcpy(np->regCarro.data, regCarro->data);
	strcpy(np->regCarro.hora, regCarro->hora);
	return &np->regCarro;
}