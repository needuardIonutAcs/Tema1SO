#include "DefineIf.h"

// // caz in care primesc #if TEST
// // iar TEST se afla in HashMap
char *cazGasitValoareHashMap(char *parametru)
{
	// vreau valoare din HashMap a lui parametru
	struct DataItem *valoare = NULL;
	valoare = search(parametru);

	if (valoare != NULL)
		return valoare->data;

	return NULL;
}

char *analizareConditieIf(char *linieCod)
{
	char s[2] = "\n ";
	char *token = NULL;
	int contor = 0;

	/* get the first token */
	token = strtok(linieCod, s);

	// #if 1, voi lua valoare 1 si o voi analiza
	while (token != NULL) {
		if (contor == 1)
			return token;

		contor++;
		token = strtok(NULL, s);
	}

	return NULL;
}

// aceata functie sare de la #if la #elif
char *sariElif(char *buffer)
{
	char *panaLaElif = NULL;

	if (buffer == NULL)
		return NULL;

	panaLaElif = strstr(buffer, "#elif");

	// daca nu am #elif, caut #else
	if (panaLaElif == NULL)
		panaLaElif = strstr(buffer, "#else");

	return panaLaElif;
}

int intoarcePrimaLinie(char *buffer)
{
	int dimBuffer = 0;
	char *bufferDupaSpatiu = NULL;
	int dimDupaSpatiu = 0;
	int dimTotal = 0;

	if (buffer == NULL)
		return 0;

	dimBuffer = strlen(buffer);

	bufferDupaSpatiu = strstr(buffer, "\n");

	if (bufferDupaSpatiu == NULL)
		return 0;

	dimDupaSpatiu = strlen(bufferDupaSpatiu);

	dimTotal = dimBuffer - dimDupaSpatiu;

	return dimTotal;
}

// afisez pana dau de #
void afisarePanaLaCaracter(char *buffer, FILE *fisierDeScris)
{
	int dim = 0;
	char *urmatorHashTag = NULL;
	int total = 0;
	char bufferFinal[100] = "";
	int dimHash = 0;

	if (buffer == NULL)
		return;

	dim = strlen(buffer);
	

	urmatorHashTag = strstr(buffer, "#elif");


	if (urmatorHashTag == NULL)
		urmatorHashTag = strstr(buffer, "#else");

	if (urmatorHashTag == NULL)
		urmatorHashTag = strstr(buffer, "#endif");

	
	dimHash = strlen(urmatorHashTag);

	total = dim - dimHash;

	memcpy(bufferFinal, buffer, total);

	fprintf(fisierDeScris, "%s", bufferFinal);
}

void altaSolutie(char *primaLinie, char *buffer, FILE *fisierDeScris)
{
	// in aceasta valoare pun ce primesc in cazul conditie
	// #if 1 sau if VAR0, mai exact 1 sau VAR0, sau orice altceva
	char *valoare = NULL;
	struct DataItem *valoareDinHash = NULL;
	int dim = 0;
	char aux[100] = "";
	char *urmatorulElif = NULL;

	if (primaLinie == NULL || buffer == NULL)
		return;

	if (strstr(primaLinie, "#if") || strstr(primaLinie, "#elif")) {
		valoare = analizareConditieIf(primaLinie);

		if (valoare == NULL)
			return;

		// caut aceasta valoare in hashMap
		valoareDinHash = search(valoare);
		// daca aceasta valoare este null, asta inseamna
		// ca nu este din hashMap, deci o analizez asa cum este
		if (valoareDinHash == NULL) {
			if (strstr(valoare, "0")) {
				// daca dau de 0, asta inseamna ca #if 0 a picat
				// deci caut sa vad daca mai am un #elseif
				// sau #else, cu alte cuvinte ma plimb pana la
				// urmatorul #
				urmatorulElif = sariElif(buffer);

				if (urmatorulElif == NULL)
					return;

				

				dim = intoarcePrimaLinie(urmatorulElif);
				

				memcpy(aux, urmatorulElif, dim);
				// trec la urmatorul #elif
				altaSolutie(aux, strstr(urmatorulElif, "\n"),
					    fisierDeScris);
			} else {
				// daca #if sau #elif trece, afiseaza tot, pana
				// dau de urmatorul #
				afisarePanaLaCaracter(buffer, fisierDeScris);
				return;
			}
		} else {
			// daca este valoarea din Hashmap, fac acelasi lucru ca
			// mai sus
			if (strstr(valoareDinHash->data, "0")) {
				urmatorulElif = sariElif(buffer);

				if (urmatorulElif == NULL)
					return;

				//int dim = 0;

				dim = intoarcePrimaLinie(urmatorulElif);
				//char aux[100] = "";

				memcpy(aux, urmatorulElif, dim);
				// trec la urmatorul #elif
				// daca dau de 0, asta inseamna ca #if 0 a picat
				// deci caut sa vad daca mai am un #elseif
				// sau #else, cu alte cuvinte ma plimb pana la
				// urmatorul #
				altaSolutie(aux, strstr(urmatorulElif, "\n"),
					    fisierDeScris);
			} else {
				// daca #if sau #elif trece, afiseaza tot, pana
				// dau de urmatorul #
				afisarePanaLaCaracter(buffer, fisierDeScris);
				return;
			}
		}
	} else {
		// daca ajung la else, afisez tot, pana la #endif
		afisarePanaLaCaracter(buffer, fisierDeScris);
		return;
	}
}

void prelucreazaDefineIf(char *linieCod, FILE *fisierPrimit,
			 FILE *fisierDeScris)
{
	// prelucrez tot de la constructia
	// #if pana la #endif
	// buffer in care voi citi
	char codCitit[500] = "";
	// buffer in care pun tot codul citit
	char buffer[500] = "";

	// citesc si pun intr-un buffer tot ce se afla
	// intre #if si #endif

	while (fgets(codCitit, 1024, fisierPrimit)) {
		if (strstr(codCitit, "#endif"))
			break;
		strcat(buffer, codCitit);
	}

	strcat(buffer, "\n#endif");

	altaSolutie(linieCod, buffer, fisierDeScris);
}
