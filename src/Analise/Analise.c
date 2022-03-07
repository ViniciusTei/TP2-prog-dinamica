#include "../../includes/Analise.h"

void plotGraph() {
  printf("\n Nao esquece de fazer isso carai");
}

// Following function extracts characters present in `src`
// between `m` and `n` (excluding `n`)
char* substr(const char *src, int m, int n)
{
    // get the length of the destination string
    int len = n - m;
 
    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
 
    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
 
    // null-terminate the destination string
    *dest = '\0';
 
    // return the destination string
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
