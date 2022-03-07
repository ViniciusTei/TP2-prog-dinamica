#ifndef MOVIMENTA
#define MOVIMENTA

#include "Analise.h"
#include "Mapa.h"

typedef struct Solucao {
  int tempo_total_gasto;
  ArrayList poisicoes;
} Solucao;

void addSolucao(ArrayList *Solucoes, Solucao nova_solucao);
void addPosicao(ArrayList *posicoes, Posicao pos);
void movimenta(Mapa *mapa, ArrayList *Solucoes, Solucao tentativa, ArrayList *pilhaDePosicoesValidas);
void atualizaPosCima(Mapa *mapa);
void atualizaPosEsquerda(Mapa *mapa);
void atualizaPosDiagEsquerda(Mapa *mapa);
void atualizaPosDiagDireita(Mapa *mapa);
int verificaEhUmNodeValido(Mapa *mapa);
int verificaEstaNoInicioDoMapa(Mapa *mapa);
void iniciaNovaSolucao(Solucao *sol);
void mostraMelhorSolucao(ArrayList Solucoes, Mapa mapa);
int verificaEhCaminhoValido(Mapa *mapa, Solucao *tentativa, ArrayList *pilhaDePosicoesValidas);

#endif