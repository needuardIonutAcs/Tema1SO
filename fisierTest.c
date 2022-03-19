#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 200

struct DataItem {
   char data[20];   
   char key[20];
};

struct DataItem* hashArray[SIZE]; 
struct DataItem* dummyItem;
struct DataItem* item;

unsigned long
hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

struct DataItem *search(char* key) {
   //get the hash
   int hashIndex = hash(key) % 100;
   //printf("hash la search%d\n", hashIndex);
	
   //move in array until an empty 
   while(hashArray[hashIndex] != NULL) {
	
      //if(hashArray[hashIndex]->key == key)
      if(strcmp(hashArray[hashIndex]->key, key) == 0)
         return hashArray[hashIndex]; 
			
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }        
	
   return NULL;        
}

void insert(char* key,char* data) {

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   strcpy(item->data, data);
   strcpy(item->key, key);
    //item->data = data;  
    //item->key = key;

   //get the hash 
    int hashIndex = hash(item->key) % 100;
    printf("hash la insert este:%d\n", hashIndex);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && strcmp(hashArray[hashIndex]->key, "invalid)") != 0) {
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }
	
   hashArray[hashIndex] = item;
}

struct DataItem* delete(struct DataItem* item) {
   //char* key = item->key;

   //get the hash 
  int hashIndex = hash(item->key) % 100;
  //int hashIndex = 0;
  //printf("hash la delete este: %d\n", hashIndex);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {
	
      //if(hashArray[hashIndex]->key == key)
      if(strcmp(hashArray[hashIndex]->key, item->key) == 0) {
         struct DataItem* temp = hashArray[hashIndex]; 
			
         //assign a dummy item at deleted position
         hashArray[hashIndex] = dummyItem; 
         return temp;
      }
		
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }      
	
   return NULL;        
}

void display() {
   int i = 0;
	
   for(i = 0; i<SIZE; i++) {
	
      if(hashArray[i] != NULL)
         printf(" (%s,%s)",hashArray[i]->key,hashArray[i]->data);
      else
         printf(" ~~ ");
   }
	
   printf("\n");
}


int main() {
   dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
   strcpy(dummyItem->data, "invalid");
   strcpy(dummyItem->key, "invalid");
    insert("a", "b");
    //insert("c", "b");
    display();

//    insert(1, 20);
//    insert(2, 70);
//    insert(42, 80);
//    insert(4, 25);
//    insert(12, 44);
//    insert(14, 32);
//    insert(17, 11);
//    insert(13, 78);
//    insert(37, 97);

   //display();
    item = search("a");

   if(item != NULL) {
      printf("Element found: %s", item->data);
   } else {
      printf("Element not found\n");
   }

    free(delete(item));
    item = search("a");

   if(item != NULL) {
      printf("Element found: %s", item->data);
   } else {
      printf("Element not found\n");
   }

   for(int i = 0; i < SIZE; i++) {
        if(hashArray[i] != NULL) {
            free(hashArray[i]);
        }
    }
}