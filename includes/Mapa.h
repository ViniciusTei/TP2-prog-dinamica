#ifndef MAPA
#define MAPA

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Colors.h"
#include "Personagem.h"

#define TRUE 1
#define FALSE 0
#define SAMUS_INDEX 0

typedef struct Mapa {
  int altura, largura;
  char ***mapa;
  int **mapa_enabled;
  Posicao posicao_atual_samus;
  int velocidade_lava;
  int tempoTotalLava;
  ArrayList personagens;
} Mapa;

void iniciaMapa(Mapa *mapa, int altura, int largura, int lava);
void insereNaPosicao(Mapa *mapa, Posicao p, char* conteudo);
int verificaPosicaoForaDeLimite(Mapa mapa, Posicao p);
void imprimeMapa(Mapa mapa, Posicao *posicao_samus) ;
void mostraNodeColorido(char *node_content);
int imprimePosicaoSamus(Posicao psamus, int x, int y);
void inserePersonagem(Mapa *mapa, char *str, Posicao pos);
char* getValorPosicao(Mapa mapa, Posicao pos);
void alteraStatusMapa(Mapa *mapa, Posicao pos);
int tempoTotalLava(int tl, int altura);
void clearMap(Mapa *mapa);
#endif