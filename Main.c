#include "PreProcesare.h"


int
main(int argc, char **argv)
{
	// fisierele de intrare si de iesire
	// in care voi citi / scrie
	FILE *inputFile, *outputFIle;
	char *fisierOuputAux;
	int i;
	int succes = 0;
	char *cale = NULL;
	// in acest fisier voi pune numele fisierului
	// de iesire
	char fisierOuput[100] = "";
	struct DataItem *hashMap =
	    (struct DataItem *)malloc(sizeof(struct DataItem));

	// daca primesc doar ./so-cpp
	if (argc == 1) {
		char caracter;
		// in caz ca primesc caractere la stdin
		//while (read(STDIN_FILENO, &caracter, 1) > 0)
		while (read(0, &caracter, 1) > 0)
			printf("%c", caracter);

		return 0;
	}



	// daca nr de argumente este 2
	if (argc == 2) {
		inputFile = fopen(argv[1], "r");
		if (inputFile == NULL)
			return -1;

		fisierOuputAux = getNumeFisierIesire(argv[1]);

		strcpy(fisierOuput, fisierOuputAux);
		free(fisierOuputAux);

		if (inputFile == NULL)
			return -1;
	} else {
		int primitOut = -1;
		// daca am fisierele .in
		// si daca am fisierele.out
		// voi seta primitOut cu 0, in caz ca primesc
		// fisierul de unde citesc si unde afisez

		// daca nr de argumente este 2
		if (argc == 3) {
			FILE *testIn = fopen(argv[1], "r");
			FILE *testOut = fopen(argv[2], "w");

			// daca primesc numele fisierelor cum trebuie
			if (testIn != NULL && testOut != NULL) {
				inputFile = fopen(argv[1], "r");
				strcpy(fisierOuput, argv[2]);
				primitOut = 0;
			}

			if (testIn != NULL)
				fclose(testIn);

			fclose(testOut);
		}

		// daca nu primesc fisierul de iesire
		// citesc argumentele
		if (primitOut == -1) {
			char caleFisier[100] = "";

			for (i = 1; i < argc; i++) {
				// daca primesc -D, inseamna ca dupa
				// urmatorul argument o sa fie o varibila
				// pe care o pun in hashMap
				if (strcmp(argv[i], "-D") == 0) {
					strcpy(caleFisier, argv[++i]);

					// adaug in hashMap, parametrul primit
					descompuneParametru(caleFisier);

					// daca primesc -DDEBUG la argument
				} else if (strcmp(argv[i], "-DDEBUG") == 0) {
					strcpy(caleFisier, argv[i]);
					descompuneParametru(caleFisier);

					inputFile = fopen(argv[2], "r");
					if (inputFile == NULL)
						return -1;

					// se face numele fisierul de iesire
					cale =
					    getNumeFisierIesire(argv[2]);
					strcpy(fisierOuput, cale);
					free(cale);

					// daca primesc -I la parametru
				} else if (strcmp(argv[i], "-I") == 0) {
					i++;
				} else {
					inputFile = fopen(argv[i], "r");
					if (inputFile == NULL)
						return -1;

					// se face numele fisierul de iesire
					cale =
					    getNumeFisierIesire(argv[i]);
					strcpy(fisierOuput, cale);
					free(cale);
				}
			}
		}
	}

	// se deschide fisierul de iesire
	// pe care l-am creat mai sus
	outputFIle = fopen(fisierOuput, "w");
	if (outputFIle == NULL)
		return -1;

	// verific daca programul a fost rezolvat cu succes
	
	// functia principala, primeste fisierul de intrare
	// si fisierul de iesire si apoi calculeaza tot
	succes = start(inputFile, outputFIle, hashMap, argv, argc);

	// in caz ca functia de mai sus crapa,
	// se elibereaza memoria si de inchid fisierele
	if (succes == -1) {
		for (i = 0; i < SIZE; i++) {
			if (hashArray[i] != NULL)
				free(hashArray[i]);
		}

		fclose(inputFile);
		fclose(outputFIle);

		// eliberare hashMap
		free(hashMap);
		return -1;
	}

	// eliberare memorie
	for (i = 0; i < SIZE; i++) {
		if (hashArray[i] != NULL)
			free(hashArray[i]);
	}

	// inchidere fisiere deschise
	fclose(inputFile);
	fclose(outputFIle);

	// eliberare memeorie HashMap
	free(hashMap);

	return 0;
}
