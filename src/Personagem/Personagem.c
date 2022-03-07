#include "../../includes/Personagem.h"

void addPersonagemToList(ArrayList *lista_personagens, Personagem personagem) {
  addItemArrayList(lista_personagens, &personagem, sizeof(Personagem));  
}

void removePersonagemById(ArrayList *lista_personagens, int id_personagem) {
  for (int i = 0; i < lista_personagens->last; i++) {
    Personagem p = *(Personagem*)lista_personagens->data[i].item;
    if (p.identificador == id_personagem) {
      removeItemInArray(lista_personagens, i);

      break ;
    };
  }
}

void imprimeListaPersonagens(ArrayList lista_personagens) {
  int inicio = lista_personagens.first;
  int fim = lista_personagens.last;

  if (lista_personagens.first == lista_personagens.last) {
    
    printf("Lista vazia!\n");
    exit(1);
  }

  for (int i = inicio; i < fim; i++) {
    Personagem personagem_atual = *(Personagem*)lista_personagens.data[i].item;

    if (personagem_atual.identificador == 0) {
      purple();
      printf("Samus\n");
      rosa();
      printf(
        "Posicao atual: %d %d\n",
        personagem_atual.posicao_no_mapa.x,
        personagem_atual.posicao_no_mapa.y
      );

      reset();
      continue;
    }

    if ( personagem_atual.t > 0) {
      laranja();
      printf("inimigo id -> %d\n", personagem_atual.identificador);
      printf("t' -> %d\n", personagem_atual.t);
      printf(
        "Posicao: %d %d\n",
        personagem_atual.posicao_no_mapa.x,
        personagem_atual.posicao_no_mapa.y
      );
      reset();
    }

  }
  
}

int isPosicaoEqual(Posicao pos_a, Posicao pos_b) {
  if (pos_a.x == pos_b.x && pos_a.y == pos_b.y) return 1;
  
  return 0;
}

Personagem getPersonagem(ArrayList lista_personagens, int index_personagem) {
  return *(Personagem*)lista_personagens.data[index_personagem].item;
}