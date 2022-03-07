#include "includes/Movimenta.h"

int main(void) {
  Mapa m;
  ArrayList Solucoes;
  Solucao tentativa;
  ArrayList pilhaUltimaPosValida;
  double tempo_gasto;
  time_t tempo_inicio, tempo_fim;
  
  initializeArrayList(&Solucoes);
  initializeArrayList(&pilhaUltimaPosValida);
  lerArquivo("entrada.txt", &m);

  printf("\nBuscando melhor caminho...");

  time(&tempo_inicio);
  movimenta(&m, &Solucoes, tentativa, &pilhaUltimaPosValida);
  time(&tempo_fim);
  printf(tempo_fim)
  tempo_gasto = tempo_fim - tempo_inicio;

  mostraMelhorSolucao(Solucoes, m);

  printf("\n Tempo gasto pelo programa: %f", tempo_gasto);
  
  return 0;
}