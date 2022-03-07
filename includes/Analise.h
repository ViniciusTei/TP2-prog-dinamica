#ifndef MOVIMENTA
#define MOVIMENTA

#include "Mapa.h"
#include <time.h>
#include <unistd.h>

void plotGraph();
void lerArquivo(char* nome_arquivo, Mapa *m);
char* substr(const char *src, int m, int n);

#endif