#ifndef INCLUDE
#define INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
//#include <unistd.h>

// Aceasta functie cauta sa primeasca:
// -I _test/inputs/test34.dir, si daca gaseste returneaza
// calea
char *citesteParametriI(char **argv, int argc);

// primesc o linie, si intorc calea din ea
char *intoarceCalea(char *linie);

// primeste o linie cu #include "calea", iar de aici se fac verificari
// si ce mai este nevoie
// daca da eroare, intoarce -1
int deschideFisierul(char *buffer, FILE *fisierDeScris,
		     char **argv, int argc);

#endif
