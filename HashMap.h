#ifndef HASHMAP
#define HASHMAP

struct DataItem {
	char data[20];
	char key[20];
};

#define SIZE 100

struct DataItem *hashArray[SIZE];
struct DataItem *item;

unsigned long hash(unsigned char *str);

struct DataItem *search(char *key);

void insert(char *key, char *data);

struct DataItem *delete(struct DataItem *item, struct DataItem *hashMap);

void display(void);

char *getValue(char *key);

struct DataItem *deleteValue(char *key);

// intorc cate elemente am puse in hash Map
int getSize(void);

#endif
