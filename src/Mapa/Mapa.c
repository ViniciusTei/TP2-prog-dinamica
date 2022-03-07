#include "../../includes/Mapa.h"

void iniciaMapa(Mapa *mapa, int altura, int largura, int lava) {
  mapa->altura = altura;
  mapa->largura = largura;
  mapa->posicao_atual_samus.x = altura - 1;
  mapa->posicao_atual_samus.y = largura - 1;
  mapa->tempoTotalLava = tempoTotalLava(lava, altura);
  
  mapa->mapa = (char***) malloc(sizeof(char**)*altura);
  mapa->mapa_enabled = (int**) malloc(sizeof(int*)*altura);

  for (int i = 0; i < altura; i++) {
    mapa->mapa[i] = (char**) malloc(sizeof(char*)*largura);
    mapa->mapa_enabled[i] = (int*) malloc(sizeof(int)*largura);

    for (int j = 0; j < largura; j++) {
      mapa->mapa[i][j] = NULL;
      mapa->mapa_enabled[i][j] = TRUE;
    }
  }

  initializeArrayList(&mapa->personagens);
  mapa->velocidade_lava = lava;

}

void insereNaPosicao(Mapa *mapa, Posicao p, char* conteudo) {
  if (verificaPosicaoForaDeLimite(*mapa, p) == 0) {
    printf("\nPos fora de limite\n");
    exit(1);
  }

  mapa->mapa[p.x][p.y] = (char*) malloc(sizeof(conteudo));
  strcpy(mapa->mapa[p.x][p.y], conteudo);

  inserePersonagem(mapa, conteudo, p);
}

void inserePersonagem(Mapa *mapa, char *str, Posicao pos) {
  Personagem personagem;
  
  personagem.identificador = mapa->personagens.last;

  if (strcmp(str, "###") == 0) {
    personagem.t = -1;
    
  } else if (strcmp(str, "000") == 0) {
    personagem.t = 0;
  } else {
    personagem.t = (int) strtol(str, (char **)NULL, 10);
  }

  personagem.posicao_no_mapa = pos;
  
  addPersonagemToList(&mapa->personagens, personagem);
}

int verificaPosicaoForaDeLimite(Mapa mapa, Posicao p) {
  if (p.x < 0 || p.y < 0) {
    return 0;
  }

  if (p.x > (mapa.altura-1) || p.y > (mapa.largura-1)) {
    return 0;
  }

  if (mapa.mapa_enabled[p.x][p.y] == FALSE) {
    return 0;
  }

  return 1;
}

void imprimeMapa(Mapa mapa, Posicao *posicao_samus) {
  printf("\n\n===== MAPA =====\n\n");
  for (int x = 0; x < mapa.altura; x++) {
    
    if (x % 2 != 0) {
      printf("  ");
    }
    
    for (int y = 0; y < mapa.largura; y++) {
      if (posicao_samus == NULL) {
         mostraNodeColorido(mapa.mapa[x][y]);
      } else if (imprimePosicaoSamus(*posicao_samus, x, y) == 0) {
        mostraNodeColorido(mapa.mapa[x][y]);
        
      }
    }
    printf("\n");
  }  

  //imprimeListaPersonagens(mapa.personagens);
}

int imprimePosicaoSamus(Posicao psamus, int x, int y) {
  if (psamus.x == x && psamus.y == y) {
    yellow();
    printf("%s ", "Sam");
    reset();
    return 1;
  }

  return 0;
}

void mostraNodeColorido(char *node_content) {
  if (strcmp(node_content, "000") == 0) {
    green();
    printf("%s ", node_content);
    reset();

    return;
  }

  if (strcmp(node_content, "###") == 0) {
    black();
    printf("%s ", node_content);
    reset();

    return;
  }

  red();
  printf("%s ", node_content);
  reset();

  return;
}

char* getValorPosicao(Mapa mapa, Posicao pos) {
  return mapa.mapa[pos.x][pos.y];
}

void alteraStatusMapa(Mapa *mapa, Posicao pos) {
  mapa->mapa_enabled[pos.x][pos.y] = mapa->mapa_enabled[pos.x][pos.y] == TRUE ? FALSE : TRUE;
}
void clearMap(Mapa *mapa){

  for(int i=0; i < mapa->largura; i++){
    for(int j=0; j < mapa->altura; j++){
      mapa->mapa_enabled[i][j] = TRUE;
    }
  }
}

int tempoTotalLava(int tl, int altura){
  return tl*altura;
}
