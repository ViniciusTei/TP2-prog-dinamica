#include "../../includes/Analise.h"

// Ao receber um array com os tempos e os tamanhos de entrada
// gera um grafico utilizando a biblioteca pbPlot
void plotGraph(double *xs, double *ys) {
  // nao permite os arrays vazios
  _Bool success;
  StringReference *errorMessage;

  double xss [] = {-2, -1, 0, 1, 2};
	double yss [] = {2, -1, -2, -1, 2};

	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = xss;
	series->xsLength = 5;
	series->ys = yss;
	series->ysLength = 5;
	series->linearInterpolation = true;
	series->lineType = L"dashed";
	series->lineTypeLength = wcslen(series->lineType);
	series->lineThickness = 2;
	series->color = GetGray(0.3);

	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 600;
	settings->height = 400;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
  settings->title = L"x^2 - 2";
  settings->titleLength = wcslen(settings->title);
  settings->xLabel = L"X axis";
  settings->xLabelLength = wcslen(settings->xLabel);
  settings->yLabel = L"Y axis";
  settings->yLabelLength = wcslen(settings->yLabel);
	ScatterPlotSeries *s [] = {series};
	settings->scatterPlotSeries = s;
	settings->scatterPlotSeriesLength = 1;

	RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	DrawScatterPlotFromSettings(canvasReference, settings);

	size_t length;
	double *pngdata = ConvertToPNG(&length, canvasReference->image);
	WriteToFile(pngdata, length, "example2.png");
	DeleteImage(canvasReference->image);
  
}

// Extrar uma substring da string passada entre os caracteres m e n
char* substr(const char *src, int m, int n) {
  int len = n - m;

  char *dest = (char*)malloc(sizeof(char) * (len + 1));

  for (int i = m; i < n && (*(src + i) != '\0'); i++){
    *dest = *(src + i);
    dest++;
  }

  *dest = '\0';

  return dest - len;
}

void lerArquivo(char* nome_arquivo, Mapa *m) {
  FILE *file;
  char linha[10000], *pLinha, *pChar, *pFrase;
  int altura, largura, tempo_samus, tempo_lava;
  file = fopen(nome_arquivo, "r");
  Posicao pos;
  int fileCurrentLine = 0, fileCurrentItem = 0;

  if(file == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    exit(1);
  }

  // ler dados iniciais
  fscanf(file, "%d %d %d %d", &altura, &largura, &tempo_samus, &tempo_lava);
  iniciaMapa(m, altura, largura, tempo_lava);

  //add Samus a lista de personagens
  Personagem Samus;
  Samus.t = tempo_samus;
  Samus.posicao_no_mapa.x = altura - 1;
  Samus.posicao_no_mapa.y = largura - 1;
  Samus.identificador = 0;
  addPersonagemToList(&m->personagens, Samus);

  char ch;
  while((ch = fgetc(file)) != EOF) {
    if (ch != '\n' && ch != ' ') {
      linha[strlen(linha)] = ch;
    }
  }
  int offset_init = 0, offset_end = 3;
  for(int i = 0; i < 5; i++) {
    pos.x = i;
    for(int j = 0; j < 5; j++) {
      pos.y = j;
      char *sub_str = substr(linha, offset_init, offset_end);
      offset_init += 3;
      offset_end += 3;
      insereNaPosicao(m, pos, sub_str);
    }
  }

  green();
  printf("\nDados iniciados\n");
  reset();
  return ;
}

void iniciaEstruturaAnalise(Analise *values) {
  values->caminhosValidosEncontrados = 0;
  values->numCaminhosEncontrados = 0;
  values->numChamadasRecursivas = 0;
}