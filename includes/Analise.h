#ifndef ANALISE
#define ANALISE

#include "Mapa.h"
#include "Plot/pbPlots.h"
#include "Plot/supportLib.h"
#include <time.h>
#include <unistd.h>

typedef struct Analise {
  int numChamadasRecursivas;
  int numCaminhosEncontrados;
  int caminhosValidosEncontrados;
} Analise;

typedef struct Celula {
  //2 flags
  int inalcancavel, inacessivel;
} Celula;

int qtd_inacessiveis(Mapa *mapa);
int temPedra(Mapa *mapa, Posicao pos);
void plotGraph(double *tempo, double *tamEntrada);
void lerArquivo(char* nome_arquivo, Mapa *m);
char* substr(const char *src, int m, int n);
void iniciaEstruturaAnalise(Analise *values);
void mostraInfos(double tempo_total, Analise val);

#endif