//#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashMap.h"

unsigned long hash(char *str)
{
	unsigned long hash = 5381;
	int c = 0;

	while ((c= *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

struct DataItem *search(char *key)
{	
	int hashIndex = 0;
	if (key == NULL)
		return NULL;

	// get the hash
	hashIndex = hash(key) % 100;

	// move in array until an empty
	while (hashArray[hashIndex] != NULL) {
		if (strcmp(hashArray[hashIndex]->key, key) == 0)
			return hashArray[hashIndex];

		// go to next cell
		++hashIndex;

		// wrap around the table
		hashIndex %= SIZE;
	}

	return NULL;
}

void insert(char *key, char *data)
{
	int hashIndex = 0;
	struct DataItem *item = NULL;
	item =
	    (struct DataItem *)malloc(sizeof(struct DataItem));

	strcpy(item->data, data);
	strcpy(item->key, key);

	// get the hash
	hashIndex = hash(item->key) % 100;

	// move in array until an empty or deleted cell
	while (hashArray[hashIndex] != NULL &&
	       strcmp(hashArray[hashIndex]->key, "invalid)") == 0) {
		// go to next cell
		++hashIndex;

		// wrap around the table
		hashIndex %= SIZE;
	}

	hashArray[hashIndex] = item;
}

struct DataItem *delete(struct DataItem *item, struct DataItem *hashMap)
{
	// get the hash
	int hashIndex = 0;
	hashIndex = hash(item->key) % 100;

	// move in array until an empty
	while (hashArray[hashIndex] != NULL) {
		if (strcmp(hashArray[hashIndex]->key, item->key) == 0) {
			struct DataItem *temp = hashArray[hashIndex];

			// assign a dummy item at deleted position
			hashArray[hashIndex] = hashMap;
			return temp;
		}

		// go to next cell
		++hashIndex;

		// wrap around the table
		hashIndex %= SIZE;
	}

	return NULL;
}

void display(void)
{
	int i = 0;

	for (i = 0; i < SIZE; i++) {

		if (hashArray[i] != NULL)
			printf(" (%s,%s)", hashArray[i]->key,
			       hashArray[i]->data);
	}

	printf("\n");
}

char *getValue(char *key)
{
	int i = 0;
	for (i = 0; i < SIZE; i++) {
		if (hashArray[i] != NULL) {
			if (strcmp(hashArray[i]->key, key) == 0)
				return hashArray[i]->data;
		}
	}
	return NULL;
}

struct DataItem *deleteValue(char *key)
{
	int i = 0;

	for (i = 0; i < SIZE; i++) {
		if (hashArray[i] != NULL) {
			if (strcmp(hashArray[i]->key, key) == 0)
				return hashArray[i];
		}
	}
	return NULL;
}

int getSize(void)
{
	int i = 0;
	int count = 0;

	for (i = 0; i < SIZE; i++) {

		if (hashArray[i] != NULL)
			count++;
	}
	return count;
}
