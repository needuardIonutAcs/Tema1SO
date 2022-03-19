#ifndef LUCRUFISIER
#define LUCRUFISIER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
//#include <windows.h>

#include "HashMap.h"

// functia modifica in sirul Buna am mere
// cuvantul Buna cu ce vreau eu
char *replaceWord(char *s, char *oldW, char *newW);

char *verificaGhilimele(char *linie);

// daca am printf("aaaa", ceva)
// vreau sa intors stringul printf("aaaa",
// atat
char *primaParte(char *linie);

// functia apeleaza o alta functie si intoarce o linie modifica
char *modificaStringul(char *linieCod, struct DataItem *hashMap);

// verific daca am functia #define
int verificaLiniaDefine(char linieCod[100]);

// in caz ca in acest buffer, am si valori de genu:
// ABC 10 ABC
// iar eu am in hashMap, ABC = 10
// va trebui sa inlocui cu: 10 10 10
char *verificaValoriDefine(char *buffer);

// daca am #define  multiplu 1 2 3
// o sa trimit 1 2 3 inapoi
char *defineMultiplu(char *linieCod, FILE *fisierPrimit);

char *modificaBufferMultipluDefine(char *buffer);

// aceasta functie insereaza in hashMap
// valorile define pe care le gaseste
// ex #define VAR0 1 + 2 + 3
// va pune in HashMap: "VAR0" "1 + 2 + 3"
void insertDefineHashMap(struct DataItem *hashMap, char *linieCod,
			 FILE *fisierPrimit);

// #undef VAR0
// si sterge VAR0 din hashMap
void stergeVariabilaMap(char *linieCod);

// daca primesc o cale de intrare returnez numele caii de iesire
// _test/outputs/test7.out voi returna: test7
char *functieCitireTest(char *linieIntrare);

// functia ce returneaza calea unde voi afisa rezultatul
// rularii codului, toata calea
// se foloseste de functia functieCitireTest pentru
// a afla numele testului pe care il pune in calea de iesire
char *getNumeFisierIesire(char *caleFisier);

// aceasta functie primeste VAR0=1
// si pune in hashMap (VAR0, 1)
void descompuneParametru(char *linieCod);

// daca am mai VAR1, VAR2 pe  o singura
// linie si trebuie sa le inlocuiesc
char *verificaIarCheie(char *linieCod);

// functia cauta sa modifice o linie, apoi sa o a afiseze
// in alt fisier
int start(FILE *fisierPrimit, FILE *fisierDeScris,
		    struct DataItem *hashMap, char **argv, int argc);

#endif
