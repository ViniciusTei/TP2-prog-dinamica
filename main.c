#include "includes/Movimenta.h"

int main(int argc, char **argv) {
  Mapa m;
  ArrayList Solucoes, tempo_total_list, tam_entrada_list;
  Solucao tentativa;
  ArrayList pilhaUltimaPosValida;
  Analise val;
  int inacessiveis;
  clock_t tempo;
  char nome_arquivo[100];
  int exit_val = FALSE;
  int readFileNameFromArgs = FALSE;
  
  iniciaEstruturaAnalise(&val);
  initializeArrayList(&Solucoes);
  initializeArrayList(&tempo_total_list);
  initializeArrayList(&tam_entrada_list);
  initializeArrayList(&pilhaUltimaPosValida);

  // quando o nome do arquivo eh passado como argumento iniciamos nossa variavel
  if (argc > 0) {
    for (int i = 0; i < argc; i++) {
      if (strcmp(argv[i], "--file") == 0 || strcmp(argv[i], "--arquivo") == 0) {
        strcpy(nome_arquivo, argv[i+1]);
        readFileNameFromArgs = TRUE;
      }
    }
  }

  do {    
    if (readFileNameFromArgs == FALSE) {
      printf("\nEntre com o nome do arquivo de entrada (se ficar em branco sera utilizado o arquivo 'entrada.txt')\n> ");

      fflush(stdin);
      fgets(nome_arquivo, sizeof(nome_arquivo), stdin);
    }
    // inicia a variavel com o nome do arquivo padrao
    // em caso de nao ter sido passada como parametro ou inicializada
    if (strlen(nome_arquivo) == 0 || strlen(nome_arquivo) == 1) {
      strcpy(nome_arquivo, "entrada.txt");
    }

    readFileNameFromArgs = FALSE;
  
    printf("\nLendo do arquivo: %s", nome_arquivo);
  
    lerArquivo("entrada.txt", &m);
  
    inacessiveis = qtd_inacessiveis(&m);
    printf("\nCelulas Inacessiveis: %d", inacessiveis);
    
    printf("\nBuscando melhor caminho...");
  
    tempo = clock(); //armazena tempo
    movimenta(&m, &Solucoes, tentativa, &pilhaUltimaPosValida, &val);
    tempo = clock() - tempo; //tempo final - tempo inicial
    
    mostraMelhorSolucao(Solucoes, m);
    
    double tempo_total = ((double)tempo)/((CLOCKS_PER_SEC/1000));
    double tam = m.altura*m.largura;
    //armazena dados da execucao para gerar o grafico
    addItemArrayList(&tempo_total_list, &tempo_total, sizeof(tempo_total));
    addItemArrayList(&tam_entrada_list, &tam, sizeof(tam));
    //imprime o tempo na tela
    mostraInfos(tempo_total, val);
    
    strcpy(nome_arquivo, "\0");
  
    printf("\nAperte 1 para finalizar ou aperte 0 para continuar\n> ");
    scanf("%d", &exit_val);
    getchar();
  } while(exit_val != TRUE);

  printf("\nPrograma finalizado!\n");
  // plot graph
  double xs [tempo_total_list.last];
	double ys [tam_entrada_list.last];

  for(int i = 0; i < tempo_total_list.last; i++) {
    xs[i] = *(double*)tempo_total_list.data[i].item;
  }

  for(int i = 0; i < tam_entrada_list.last; i++) {
    ys[i] = *(double*)tam_entrada_list.data[i].item;
  }
  
  plotGraph(xs, ys);

 return 0;
}
