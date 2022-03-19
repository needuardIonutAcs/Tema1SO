#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
//#include <unistd.h>

#include "Garzi.h"
#include "Include.h"
#include "DefineIf.h"
#include "HashMap.h"


// functia modifica in sirul Buna am mere
// cuvantul Buna cu ce vreau eu
char *replaceWord(char *s, char *oldW, char *newW)
{
	char *result = NULL;
	int i = 0, cnt = 0;
	int newWlen = strlen(newW);
	int oldWlen = strlen(oldW);

	// Counting the number of times old word
	// occur in the string
	for (i = 0; s[i] != '\0'; i++) {
		if (strstr(&s[i], oldW) == &s[i]) {
			cnt++;
			// Jumping to index after the old word.
			i += oldWlen - 1;
		}
	}

	// Making new string of enough length
	result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);

	i = 0;
	while (*s) {
		// compare the substring with the result
		if (strstr(s, oldW) == s) {
			strcpy(&result[i], newW);
			i += newWlen;
			s += oldWlen;

		} else
			result[i++] = *s++;
	}

	result[i] = '\0';
	return result;
}

char *verificaGhilimele(char *linie)
{
	int contor = 0;
	static const char s[2] = "\"";
	char *token = NULL;

	if (strstr(linie, "\"") == NULL)
		return NULL;


	/* get the first token */
	token = strtok(linie, s);

	/* walk through other tokens */
	while (token != NULL) {
		if (contor == 2)
			return token;

		contor++;
		token = strtok(NULL, s);
	}

	return NULL;
}

// daca am printf("aaaa", ceva)
// vreau sa intors stringul printf("aaaa",
// atat
char *primaParte(char *linie)
{
	int contor = 0;
	int once = 0;
	static const char s[5] = "\"";
	char *token = NULL;
	char *buffer = calloc(500, sizeof(char));
	/* get the first token */
	token = strtok(linie, s);

	/* walk through other tokens */
	while (token != NULL) {
		if (contor < 2) {
			if (once == 0) {
				strcat(buffer, token);
				strcat(buffer, "\"");
				once = -1;
			} else {
				strcat(buffer, token);
			}
		}

		contor++;
		token = strtok(NULL, s);
	}

	return buffer;
}

// functia apeleaza o alta functie si intoarce o linie modifica
char *modificaStringul(char *linieCod, struct DataItem *hashMap)
{
	char *result2 = NULL;
	int i;
	char aux[100] = "\"";

	for (i = 0; i < SIZE; i++) {
		if (hashArray[i] != NULL) {
			if (strstr(linieCod, hashArray[i]->key) &&
			    strcmp(hashArray[i]->data, "") != 0) {

				char *copieLinieCod = strdup(linieCod);
				char *copieLinieCod2 = strdup(linieCod);

				char *verificare =
				    verificaGhilimele(copieLinieCod);
				if (verificare != NULL) {
					char *bucata =
					    primaParte(copieLinieCod2);

					if (bucata != NULL) {
						result2 = replaceWord(
						    verificare,
						    hashArray[i]->key,
						    hashArray[i]->data);

						

						strcat(aux, result2);
						strcat(bucata, aux);
						free(result2);
						free(copieLinieCod);
						free(copieLinieCod2);

						return bucata;
					}
				} else {
					result2 = replaceWord(
					    linieCod, hashArray[i]->key,
					    hashArray[i]->data);
				}
				free(copieLinieCod);
				free(copieLinieCod2);

				return result2;
			}
		}
	}

	return linieCod;
}

// verific daca am functia #define
int verificaLiniaDefine(char linieCod[100])
{
	if (strstr(linieCod, "#define"))
		return -1;
	else if (strstr(linieCod, "#undef"))
		return -2;
	else if (strstr(linieCod, "#ifndef"))
		return -5;
	else if (strstr(linieCod, "#ifdef"))
		return -4;
	else if (strstr(linieCod, "#if"))
		return -3;
	else if (strstr(linieCod, "#include"))
		return -6;

	return 0;
}

// in caz ca in acest buffer, am si valori de genu:
// ABC 10 ABC
// iar eu am in hashMap, ABC = 10
// va trebui sa inlocui cu: 10 10 10
char *verificaValoriDefine(char *buffer)
{
	static const char s[5] = " ";
	char *token = NULL;
	char bufferNou[100] = "";
	char linie[100] = "";
	char buffeNou[40] = "";
	char *linieModif = malloc(100);

	if (buffer == NULL)
		return buffer;

	/* get the first token */
	token = strtok(buffer, s);
	

	if (linie != NULL) {
		/* walk through other tokens */
		while (token != NULL) {
			// acest token il compar cu ce am in HashMap
			// si daca il gasesc concatenez la buffer
			char *linieModificata = modificaStringul(token, NULL);

			if (linieModificata != NULL) {
				strcat(linie, linieModificata);
				strcat(linie, " ");
				if (strcmp(linieModificata, token) != 0)
					free(linieModificata);
			}

			token = strtok(NULL, s);
		}


		memcpy(bufferNou, linie, strlen(linie) - 1);
		memcpy(linie, bufferNou, strlen(bufferNou));
	}

	

	strcpy(linieModif, linie);

	return linieModif;
}

// daca am #define  multiplu 1 2 3
// o sa trimit 1 2 3 inapoi
char *defineMultiplu(char *linieCod, FILE *fisierPrimit)
{
	char codCitit[30] = "";
	char buffer[200] = "";
	char *bufferNou = NULL;

	if (strstr(linieCod, "\\")) {
		strcat(buffer, linieCod);
		strcat(buffer, " ");

		while (fgets(codCitit, 1024, fisierPrimit)) {
			if (strstr(codCitit, "\\")) {
				strcat(buffer, codCitit);
				strcat(buffer, " ");
			} else {
				strcat(buffer, codCitit);
				strcat(buffer, " ");
				break;
			}
		}
	} else {
		return NULL;
	}

	bufferNou = malloc(200);

	strcpy(bufferNou, buffer);

	return bufferNou;
}

char *modificaBufferMultipluDefine(char *buffer)
{
	static const char s[5] = "\\\n ";
	char *token = NULL;
	char newBuffer[100] = "";
	int count = 0;
	char *finalBuffer = NULL;

	/* get the first token */
	token = strtok(buffer, s);

	/* walk through other tokens */
	while (token != NULL) {
		strcat(newBuffer, token);
		strcat(newBuffer, " ");
		token = strtok(NULL, s);
		count = strlen(newBuffer);
	}

	

	finalBuffer = calloc(200, sizeof(char));
	if (finalBuffer == NULL)
		return NULL;

	memcpy(finalBuffer, newBuffer, count - 1);

	return finalBuffer;
}

// aceasta functie insereaza in hashMap
// valorile define pe care le gaseste
// ex #define VAR0 1 + 2 + 3
// va pune in HashMap: "VAR0" "1 + 2 + 3"
void insertDefineHashMap(struct DataItem *hashMap, char *linieCod,
			 FILE *fisierPrimit)
{
	char copieCod[100] = "";
	int contor = 0;
	char cheie[10] = "";
	char data[10] = "";
	char cuvant[100] = "";
	char buffer[100] = "";
	// este pus -1, pentru a nu copia si terminatorul
	int nr = 0;
	static const char s[2] = " ";
	char *token = NULL;
	char *bufferNou = NULL;
	char *bufferNouModif = NULL;

	nr = strlen(linieCod) - 1;
	memcpy(copieCod, linieCod, nr);

	/* get the first token */
	token = strtok(copieCod, s);

	/* walk through other tokens */
	while (token != NULL) {
		if (contor == 1)
			strcpy(cheie, token);
		if (contor > 1) {
			strcat(cuvant, token);
			strcat(cuvant, " ");
		}
		contor++;
		token = strtok(NULL, s);
	}
	nr = 0;
	nr = strlen(cuvant) - 1;
	memcpy(buffer, cuvant, nr);
	// in caz ca in acest buffer, am si valori de genu:
	// ABC 10 ABC
	// iar eu am in hashMap, ABC = 10
	// va trebui sa inlocui cu: 10 10 10
	bufferNou = verificaValoriDefine(buffer);

	// daca acest buffer se termina cu \
   // o sa mai citesc din fisier pana cand un buffer nu mai are \

	// printf("inainte: %s\n", bufferNou);
	bufferNouModif = defineMultiplu(bufferNou, fisierPrimit);

	if (bufferNouModif == NULL) {
		insert(cheie, bufferNou);
	} else {
		// in acest caz inseamna ca am un define multiplu
		// acum voi imparti cum trebuie acest string
		char *dataModif = modificaBufferMultipluDefine(bufferNouModif);

		insert(cheie, dataModif);
		free(bufferNouModif);
		free(dataModif);
	}

	// printf("dupa: %s\n", bufferNouModif);

	if (strcmp(buffer, bufferNou) != 0)
		free(bufferNou);
}

// #undef VAR0
// si sterge VAR0 din hashMap
void stergeVariabilaMap(char *linieCod)
{

	static const char s[2] = " ";
	char *token;
	int contor = 0;
	char cheieDeSters[20] = "";
	struct DataItem *cheie = NULL;

	/* get the first token */
	token = strtok(linieCod, s);

	/* walk through other tokens */
	while (token != NULL) {
		if (contor == 1)
			memcpy(cheieDeSters, token, strlen(token) - 1);

		contor++;
		token = strtok(NULL, s);
	}

	cheie = search(cheieDeSters);

	if (cheie != NULL) {
		struct DataItem *dummyItem =
		    (struct DataItem *)malloc(sizeof(struct DataItem));
		strcpy(dummyItem->data, "invalid");
		strcpy(dummyItem->key, "invalid");
		free(delete(cheie, dummyItem));
	}
}

// daca primesc o cale de intrare returnez numele caii de iesire
// _test/outputs/test7.out voi returna: test7
char *functieCitireTest(char *linieIntrare)
{
	static const char s[100] = "/.";
	char *token = NULL;

	token = strtok(linieIntrare, s);
	while (token != NULL) {
		token = strtok(NULL, s);
		// compar token-ul cu test..
		if (strstr(token, "test") != 0)
			return token;
	}
	return NULL;
}

// functia ce returneaza calea unde voi afisa rezultatul
// rularii codului, toata calea
// se foloseste de functia functieCitireTest pentru
// a afla numele testului pe care il pune in calea de iesire
char *getNumeFisierIesire(char *caleFisier)
{
	char fisierIntrareCopie[50] = "";
	char *fisierIesireNume = calloc(50, sizeof(char));
	char *numeTestIntrare = NULL;

	memcpy(fisierIntrareCopie, caleFisier, strlen(caleFisier));
	fisierIntrareCopie[strlen(caleFisier)] = '\0';
	numeTestIntrare = functieCitireTest(fisierIntrareCopie);

	if (numeTestIntrare != NULL) {
		strcat(fisierIesireNume, "_test/outputs/");
		strcat(fisierIesireNume, numeTestIntrare);
		strcat(fisierIesireNume, ".out");
	}

	return fisierIesireNume;
}

// aceasta functie primeste VAR0=1
// si pune in hashMap (VAR0, 1)
void descompuneParametru(char *linieCod)
{
	static const char s[5] = " =";
	char *token = NULL;
	int contor = 0;
	char cheie[20] = "";
	char data[20] = "";

	/* get the first token */
	token = strtok(linieCod, s);

	/* walk through other tokens */
	while (token != NULL) {
		if (contor == 0)
			strcpy(cheie, token);

		if (contor == 1)
			strcpy(data, token);

		token = strtok(NULL, s);

		contor++;
	}

	insert(cheie, data);
}

// daca am mai VAR1, VAR2 pe  o singura
// linie si trebuie sa le inlocuiesc
char *verificaIarCheie(char *linieCod)
{
	int i;
	for (i = 0; i < SIZE; i++) {
		if (hashArray[i] != NULL) {
			if (strstr(linieCod, hashArray[i]->key) &&
			    strcmp(hashArray[i]->data, "") != 0) {
				return modificaStringul(linieCod, NULL);
			}
		}
	}
	return NULL;
}

// functia cauta sa modifice o linie, apoi sa o a afiseze
// in alt fisier
int start(FILE *fisierPrimit, FILE *fisierDeScris,
		    struct DataItem *hashMap, char **argv, int argc)
{
	int gasitMain = 0;
	char codCitit[30] = "";

	while (fgets(codCitit, 1024, fisierPrimit)) {
		// fac o copie si o trimit mai departe pentru inspectare
		char copieCodCitit[30] = "";
		char copieCodCititDefine[30] = "";
		// fac copie pt a modifica fara griji
		strcpy(copieCodCitit, codCitit);
		strcpy(copieCodCititDefine, codCitit);

		// daca am define-uri nu am voie sa le afisez
		if (verificaLiniaDefine(copieCodCitit) == 0) {
			// modific fiecare linie in parte

			char *linieModificata =
			    modificaStringul(copieCodCitit, hashMap);

			// in caz ca am mai multe aparitii ale mai multor VAR1,
			// VAR2 pe aceeasi linie
			char *iar = verificaIarCheie(linieModificata);


			// cand dau de main anunt, pentru a putea afisa in
			// fisier
			if (strstr(linieModificata, "int main"))
				gasitMain = 1;

			// dupa ce am gasit main-ul afisez restu de linii
			if (gasitMain == 1) {
				if (strcmp(linieModificata, "\n") != 0) {
					if (iar != NULL) {
						fprintf(fisierDeScris, "%s",
							iar);
						free(iar);
					} else {
						fprintf(fisierDeScris, "%s",
							linieModificata);
					}
				}
			}
			if (strcmp(linieModificata, copieCodCitit) != 0)
				free(linieModificata);

		} else if (verificaLiniaDefine(copieCodCitit) == -2) {
			stergeVariabilaMap(copieCodCitit);

		} else if (verificaLiniaDefine(copieCodCitit) == -3) {
			// caz in care dau de #if
			prelucreazaDefineIf(copieCodCititDefine, fisierPrimit,
					    fisierDeScris);
		} else if (verificaLiniaDefine(copieCodCitit) == -4) {
			// #ifdef
			prelucreazaIfDef(copieCodCititDefine, fisierPrimit,
					 fisierDeScris);

		} else if (verificaLiniaDefine(copieCodCitit) == -5) {
			// #ifndef
			prelucreazaIfNdef(copieCodCititDefine, fisierPrimit,
					  fisierDeScris);
		} else if (verificaLiniaDefine(copieCodCitit) == -6) {
			// #include "cale-fisier"
			int valoare = 0;

			valoare = deschideFisierul(copieCodCitit, fisierPrimit,
						   fisierDeScris, argv, argc);
			// daca incerc sa deschid un fisier inexistent, afisez
			// eroare
			if (valoare == -1)
				return -1;

		} else {
			// in caz ca am define
			insertDefineHashMap(hashMap, copieCodCititDefine,
					    fisierPrimit);
		}
	}

	// caz in care nu am main, dar tot pot sa afisez in alt fisier
	if (gasitMain == 0) {
		fseek(fisierPrimit, 0, SEEK_SET);
		while (fgets(codCitit, 1024, fisierPrimit)) {
			if (strstr(codCitit, "define") == NULL &&
			    strstr(codCitit, "#ifndef") == NULL &&
			    strstr(codCitit, "#endif") == NULL &&
			    strcmp(codCitit, "\n")) {

				fprintf(fisierDeScris, "%s", codCitit);
			}
		}
	}
	return 0;
}
