#ifndef REGISTO_H
#define REGISTO_H
#include "structs.h"

unsigned hash(char *s);
RegCarroNode *procura(char *s, RegCarroList hashtab[HASHSIZE]);
RegCarroNode *install(RegCarro *regCarro, RegCarroList hashtab[HASHSIZE]);
#endif // REGISTO_H