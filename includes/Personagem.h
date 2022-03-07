#ifndef PERSONAGEM
#define PERSONAGEM

#include "Colors.h"
#include "ArrayList.h"

typedef struct Posicao {
  int x, y;
} Posicao;

typedef struct Personagem {
  int identificador;
  int t;
  Posicao posicao_no_mapa;
} Personagem;

void addPersonagemToList(ArrayList *lista_personagens, Personagem personagem);
void imprimeListaPersonagens(ArrayList lista_personagens);
void removePersonagemById(ArrayList *lista_personagens, int id_personagem);
int isPosicaoEqual(Posicao pos_a, Posicao pos_b);
Personagem getPersonagem(ArrayList lista_personagens, int index_personagem);

#endif