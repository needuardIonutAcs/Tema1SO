#include "Include.h"
#include "PreProcesare.h"

// primesc o linie, si intorc calea din ea
//#include "cale" -> cale
char *intoarceCalea(char *linie)
{
	static const char s[3] = "\"";
	char *token = NULL;
	int contor = 0;

	/* get the first token */
	token = strtok(linie, s);

	/* walk through other tokens */
	while (token != NULL) {
		if (contor == 1)
			return token;

		contor++;
		token = strtok(NULL, s);
	}
	return NULL;
}

// Aceasta functie cauta sa primeasca:
// -I _test/inputs/test34.dir, si daca gaseste returneaza
// calea
char *citesteParametriI(char **argv, int argc)
{
	int i = 0;
	for (i = 0; i < argc; i++)
		if (strstr(argv[i], "-I"))
			return argv[++i];

	return NULL;
}

// primesc o linie, si fac prelucrari pe ea, deschid fisiere, adaug
// din fisier in fisier pentru cand am #include
int deschideFisierul(char *buffer, FILE *fisierDeScris,
		     char **argv, int argc)
{
	char *caleFisier = NULL;
	char caleToataFisier[100] = "";
	int check = 0;
	FILE *fisier = NULL;
	FILE *fisierNou = NULL;
	char *fisierParam = NULL;

	caleFisier = intoarceCalea(buffer);
	

	if (caleFisier != NULL) {
		strcat(caleToataFisier, "_test/inputs/");
		strcat(caleToataFisier, caleFisier);

		fisier = fopen(caleToataFisier, "r");

		if (fisier == NULL)
			check = 1;

		if (fisier == NULL) {
			fisierParam = citesteParametriI(argv, argc);

			if (fisierParam != NULL) {
				check = 0;
				strcat(fisierParam, "/");
				strcat(fisierParam, caleFisier);

				fisierNou = fopen(fisierParam, "r");

				if (fisierNou != NULL) {
					start(fisierNou, fisierDeScris,
					      argv, argc);
					fclose(fisierNou);
				} else {
					return -1;
				}
			}
		}

		if (check == 1)
			return -1;

		// acum, citesc din fisier si afizez in fisierul meu
		if (fisier != NULL) {
			start(fisier, fisierDeScris, argv, argc);

			if (fisier != NULL)
				fclose(fisier);
		}
	}

	return 0;
}
