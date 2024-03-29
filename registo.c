#include "registo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned hash(char *s) {
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

// lookup: pesquisa s na hashtab e retorna todas as aparencias
RegCarro *lookup(char *s,RegCarroNode *hashtab[HASHSIZE]) {
	RegCarroNode *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->regCarro.matricula) == 0)
			return &np->regCarro;
	return NULL;
}

// VER SE TA BEM
RegCarro *install(RegCarro *regCarro, RegCarroNode *hashtab[HASHSIZE]) {
	RegCarroNode *np;
	unsigned hashval;

	if ((np = (RegCarroNode *) malloc(sizeof(RegCarroNode))) == NULL)
		return NULL;
	hashval = hash(regCarro->matricula);
	np->next = hashtab[hashval];
	hashtab[hashval] = np;
	np->regCarro = *regCarro;
	return &np->regCarro;
}