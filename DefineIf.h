#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
//#include <unistd.h>

#include "HashMap.h"

// // caz in care primesc #if TEST
// // iar TEST se afla in HashMap
char *cazGasitValoareHashMap(char *parametru, char *buffer);

char *analizareConditieIf(char *linieCod);

// aceata functie sare de la #if la #elif
char *sariElif(char *buffer);

int intoarcePrimaLinie(char *buffer);

// afisez pana dau de #
void afisarePanaLaCaracter(char *buffer, FILE *fisierDeScris);

void altaSolutie(char *primaLinie, char *buffer, FILE *fisierDeScris);

void prelucreazaDefineIf(char *linieCod, FILE *fisierPrimit,
			 FILE *fisierDeScris);