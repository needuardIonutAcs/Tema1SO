#ifndef GARZI
#define GARZI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
//#include <unistd.h>

// de aici incep prelucrarea pe #ifndef
void prelucreazaIfNdef(char *buffer, FILE *fisierPrimit, FILE *fisierDeScris);

// de aici incep prelucrarea pe #ifdef
void prelucreazaIfDef(char *buffer, FILE *fisierPrimit, FILE *fisierDeScris);

#endif
