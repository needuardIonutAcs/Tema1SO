#include "Garzi.h"
#include "DefineIf.h"
#include "PreProcesare.h"

// de aici incep prelucrarea pe #ifndef
void prelucreazaIfNdef(char *buffer, FILE *fisierPrimit)
{
	char codCitit[500] = "";
	char bufferPrincipal[500] = "";
	char *valoare = NULL;
	char *valoareDinHashMap = NULL;

	// citesc si pun intr-un buffer tot ce se afla
	// intre #if si #endif
	while (fgets(codCitit, 1024, fisierPrimit)) {
		if (strstr(codCitit, "#endif"))
			break;

		strcat(bufferPrincipal, codCitit);
	}

	// #ifdef VAR
	// caut sa vad daca am var in HashMap
	valoare = analizareConditieIf(buffer);

	if (valoare != NULL) {
		valoareDinHashMap = cazGasitValoareHashMap(valoare);

		if (valoareDinHashMap != NULL) {
			// daca nu am nu fac nimic

		} else {
			// pentru ca nu am gasit valoarea
			// va trebui sa fac ce se afla intre garzi

			if (verificaLiniaDefine(bufferPrincipal) == -1) {
				// printf("%s", bufferPrincipal);
				insertDefineHashMap(bufferPrincipal,
						    fisierPrimit);
			}
		}
	}
}

// de aici incep prelucrarea pe #ifdef
void prelucreazaIfDef(char *buffer, FILE *fisierPrimit)
{
	char codCitit[500] = "";
	char bufferPrincipal[500] = "";
	char *valoare = NULL;
	char *valoareDinHashMap = NULL;

	// citesc si pun intr-un buffer tot ce se afla
	// intre #if si #endif
	while (fgets(codCitit, 1024, fisierPrimit)) {
		if (strstr(codCitit, "#endif"))
			break;

		strcat(bufferPrincipal, codCitit);
	}

	// #ifdef VAR
	// caut sa vad daca am var in HashMap
	valoare = analizareConditieIf(buffer);

	if (valoare != NULL) {
		valoareDinHashMap = cazGasitValoareHashMap(valoare);

		if (valoareDinHashMap != NULL) {
			// daca gasesc ceva, voi face
			if (verificaLiniaDefine(bufferPrincipal) == -2)
				stergeVariabilaMap(valoareDinHashMap);
		}
	}

	// acum caut daca am VAR in hashMap
}
