#ifndef ARRAYLIST
#define ARRAYLIST

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ARRAY_SIZE 10000

typedef struct Node {
  void *item;
} Node;

typedef struct ArrayList {
  Node data[MAX_ARRAY_SIZE];
  int first, last;
} ArrayList;

//initialize 
void initializeArrayList(ArrayList *list);
//add
void addItemArrayList(ArrayList *list, void *item, unsigned long int item_size);
//remove
void removeItemInArray(ArrayList *list, int index_to_remove);

#endif