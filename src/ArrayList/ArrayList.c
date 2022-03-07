#include "../../includes/ArrayList.h"

void initializeArrayList(ArrayList *list) {
  list->first = 0;
  list->last = list->first;
}

void addItemArrayList(ArrayList *list, void *item, unsigned long int item_size) {
  if (list->last == MAX_ARRAY_SIZE) {
    // lista esta cheia
    exit(1);
  }

  int last_index = list->last;

  list->data[last_index].item = malloc(item_size);
  memcpy(list->data[last_index].item, item, item_size);

  list->last += 1;
}

void removeItemInArray(ArrayList *list, int index_to_remove) {
  //lista esta vazia
  if (list->first == list->last || index_to_remove >= list->last) {
    printf("\nErro ao remover da lista. \nLista vazia");
    exit(1);
  }

  Node to_remove = list->data[index_to_remove];

  for (int aux = index_to_remove; aux < list->last - 1; aux++) {
    list->data[aux] = list->data[aux + 1];
  }
  list->last -= 1;
  free(to_remove.item);
};