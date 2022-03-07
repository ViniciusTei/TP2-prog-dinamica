#include "../../includes/Movimenta.h"

void addSolucao(ArrayList *Solucoes, Solucao nova_solucao) {
  addItemArrayList(Solucoes, &nova_solucao, sizeof(nova_solucao));
}

void addPosicao(ArrayList *posicoes, Posicao pos) {
  addItemArrayList(posicoes, &pos, sizeof(pos));
}

void iniciaNovaSolucao(Solucao *sol) {
  sol = (Solucao*) malloc(sizeof(Solucao));
  sol->tempo_total_gasto = 0;
  initializeArrayList(&sol->poisicoes);

}

int verificaEstaNoInicioDoMapa(Mapa *mapa) {
  if (mapa->posicao_atual_samus.x == mapa->altura - 1) {
    return TRUE;
  }

  return FALSE;
}

int verificaEhUmNodeValido(Mapa *mapa) {
  if (strcmp(getValorPosicao(*mapa, mapa->posicao_atual_samus), "###") == 0) {

    return FALSE;
  }

  return TRUE;
}

void atualizaPosCima(Mapa *mapa) {
  if (mapa->posicao_atual_samus.x < 0) {
    exit(1);
  }
  
  mapa->posicao_atual_samus.x --;
}

void atualizaPosEsquerda(Mapa *mapa) {
  if (mapa->posicao_atual_samus.y < 0) {
    exit(1);
  }
  
  mapa->posicao_atual_samus.y--;
}

void atualizaPosDireita(Mapa *mapa) {
  if (mapa->posicao_atual_samus.y < 0) {
    exit(1);
  }
  
  mapa->posicao_atual_samus.y++;
}

void atualizaPosDiagEsquerda(Mapa *mapa) {
  mapa->posicao_atual_samus.x --;
  mapa->posicao_atual_samus.y--;
}

void atualizaPosDiagDireita(Mapa *mapa) {
  mapa->posicao_atual_samus.x --;
  mapa->posicao_atual_samus.y++;
}

int verificaEhCaminhoValido(Mapa *mapa, Solucao *tentativa, ArrayList *pilhaDePosicoesValidas) {
  if (mapa->posicao_atual_samus.x == 0) {
    int soma = 0;
    for (int i = 0; i < pilhaDePosicoesValidas->last; i++) {
      Posicao posicao = *(Posicao*) pilhaDePosicoesValidas->data[i].item;
      char *valorPosString = getValorPosicao(*mapa, posicao);
      int valorPos = (int) strtol(valorPosString, (char **)NULL, 10);

      soma += valorPos;
    }
    Personagem samus = getPersonagem(mapa->personagens, SAMUS_INDEX);
    soma = soma + (samus.t * mapa->altura);
    tentativa->tempo_total_gasto = soma;

    if ((mapa->velocidade_lava * mapa->altura) >= soma) {

      return TRUE;
    }
    
  }

  return FALSE;
}

int calculaTempoGasto(Mapa *mapa) {
  Personagem samus = getPersonagem(mapa->personagens, SAMUS_INDEX);
  Personagem per;
  
  for (int i = SAMUS_INDEX + 1; i < mapa->personagens.last; i++) {
    per = getPersonagem(mapa->personagens, i);
    if (isPosicaoEqual(mapa->posicao_atual_samus, per.posicao_no_mapa) == TRUE) {
      return per.t + samus.t;
    }
  }
  return samus.t;
}

void addPosicaoPilha(ArrayList *pilha, Posicao pos) {
   addItemArrayList(pilha, &pos, sizeof(Posicao));
}

void removePosicaoPilha(ArrayList *pilha) {
  if (pilha->last != pilha->first) {
    removeItemInArray(pilha, pilha->last - 1);
    
  }
}

void movimenta(Mapa *mapa, ArrayList *Solucoes, Solucao tentativa, ArrayList *pilhaDePosicoesValidas) {
  int resultado_validacao, ehInicioMapa = verificaEstaNoInicioDoMapa(mapa);
  Posicao ultimaPosValida, posicao_desejada; 
  Posicao primeira_pos = *(Posicao*) pilhaDePosicoesValidas->data[0].item;
  if (pilhaDePosicoesValidas->last != pilhaDePosicoesValidas->first) {
    ultimaPosValida = *(Posicao*) pilhaDePosicoesValidas->data[pilhaDePosicoesValidas->last - 1].item;
  }
  
  if (verificaEhUmNodeValido(mapa) == FALSE) {
    // se nao for um node valido e estamos no fundo da caverna
    // devemos andar para a esquerda
    //enquanto Y !=0 && ehInicioMapa == TRUE && posição samus.x == altura-1
    while((ehInicioMapa == TRUE) && (mapa->posicao_atual_samus.x == mapa->altura-1)) {
      if (pilhaDePosicoesValidas->last != pilhaDePosicoesValidas->first) {
        //restart de pilha + mapa
        clearMap(mapa);
        initializeArrayList(pilhaDePosicoesValidas);
      }
      atualizaPosEsquerda(mapa);
      movimenta(mapa, Solucoes, tentativa, pilhaDePosicoesValidas);
      ehInicioMapa = verificaEstaNoInicioDoMapa(mapa);
    }
    // se nao for um node valido e estamos acima do fundo apenas voltamos
    //desempilha ultima posição valida caso a minha atual seja igual a ultima válida
    alteraStatusMapa(mapa, mapa->posicao_atual_samus);
    ultimaPosValida = *(Posicao*) pilhaDePosicoesValidas->data[pilhaDePosicoesValidas->last - 1].item;
    mapa->posicao_atual_samus.x = ultimaPosValida.x;
    mapa->posicao_atual_samus.y = ultimaPosValida.y;
    return; 
  } else {
    if(mapa->posicao_atual_samus.x != ultimaPosValida.x){
      //armazerna posicao valida em uma variavel
      ultimaPosValida = mapa->posicao_atual_samus;
      addPosicaoPilha(pilhaDePosicoesValidas, ultimaPosValida);
    }
  }

  // se estamos no fundo da caverna e eh um node valido
  // criamos uma nova tentativa
  if (ehInicioMapa == TRUE) {
    iniciaNovaSolucao(&tentativa);
  }

  // se estamos no topo e o tempo total <= velocidade da lava * altura
  // encontramos uma solucao valida! salva tentativa no array solucoes
  if (verificaEhCaminhoValido(mapa, &tentativa, pilhaDePosicoesValidas) == TRUE) {
    for(int i = 0; i < pilhaDePosicoesValidas->last; i++) {
      addPosicao(&tentativa.poisicoes, *(Posicao*) pilhaDePosicoesValidas->data[i].item);
    }
    addSolucao(Solucoes, tentativa);
    tentativa.tempo_total_gasto = 0;
    initializeArrayList(&tentativa.poisicoes);
    //se x for igual a 0 então temos que finalizar esse caminho
    if(mapa->posicao_atual_samus.x == 0){
      for(int i = 0; i < pilhaDePosicoesValidas->last; i++) {
        Posicao posicao_atual =  *(Posicao*) pilhaDePosicoesValidas->data[i].item;
;
      }
    }

    //volta para o comeco
    return;
  }

  //x == impar então so posso ir para cima e diagonal direita
  //x == par so posso ir para cima e diagonal esquerda
  //Se x == 0 pula tudo;
  if(mapa->posicao_atual_samus.x != 0){
    posicao_desejada = mapa->posicao_atual_samus;
    // tenta ir para cima
    posicao_desejada.x--;
    resultado_validacao = verificaPosicaoForaDeLimite(*mapa, posicao_desejada);
    if(resultado_validacao == 1){
      atualizaPosCima(mapa);
      movimenta(mapa, Solucoes, tentativa, pilhaDePosicoesValidas);
    } 
  }
  if(mapa->posicao_atual_samus.x != 0){
    posicao_desejada = mapa->posicao_atual_samus;
    // tenta ir para diagonal esquerda
    posicao_desejada.x--;
    posicao_desejada.y--;
    resultado_validacao = verificaPosicaoForaDeLimite(*mapa, posicao_desejada);
    if((resultado_validacao == 1)&&(mapa->posicao_atual_samus.x % 2 == 0)){
      atualizaPosDiagEsquerda(mapa);
      movimenta(mapa, Solucoes, tentativa, pilhaDePosicoesValidas);
    }
  }
  if(mapa->posicao_atual_samus.x != 0){
    posicao_desejada = mapa->posicao_atual_samus;
    // tenta ir para diagonal direita
    posicao_desejada.x--;
    posicao_desejada.y++;
    resultado_validacao = verificaPosicaoForaDeLimite(*mapa, posicao_desejada);
    if((resultado_validacao == 1)&&(mapa->posicao_atual_samus.x % 2 == 1)){
      atualizaPosDiagDireita(mapa);
      movimenta(mapa, Solucoes, tentativa, pilhaDePosicoesValidas);
    }
  }
  
  primeira_pos = *(Posicao*) pilhaDePosicoesValidas->data[0].item;
  if ((primeira_pos.x != mapa->posicao_atual_samus.x)&&(primeira_pos.y != mapa->posicao_atual_samus.y)) {
    removePosicaoPilha(pilhaDePosicoesValidas);
    ultimaPosValida = *(Posicao*) pilhaDePosicoesValidas->data[pilhaDePosicoesValidas->last - 1].item;
    alteraStatusMapa(mapa, mapa->posicao_atual_samus);
    mapa->posicao_atual_samus.x = ultimaPosValida.x;
    mapa->posicao_atual_samus.y = ultimaPosValida.y;
  }else{
    initializeArrayList(pilhaDePosicoesValidas);
    alteraStatusMapa(mapa, mapa->posicao_atual_samus);
    addPosicaoPilha(pilhaDePosicoesValidas, primeira_pos);
    mapa->posicao_atual_samus.x = primeira_pos.x;
    mapa->posicao_atual_samus.y = primeira_pos.y;
  }
  return;
}


void mostraMelhorSolucao(ArrayList Solucoes, Mapa mapa) {
  
  if (Solucoes.first == Solucoes.last) {
    red();
    printf("\nSamus falhou na missao \n\n");
    reset();
    return;
  }
  
  Solucao melhor = *(Solucao*)Solucoes.data[0].item;
  for (int i = 0; i < Solucoes.last; i++) {
    Solucao solucao_atual = *(Solucao*)Solucoes.data[i].item;
    if (solucao_atual.tempo_total_gasto < melhor.tempo_total_gasto) {
       melhor = solucao_atual;
   }
  }

  
  sleep(2);
  clearScreen();
  for (int i = melhor.poisicoes.first; i < melhor.poisicoes.last; i++) {
    printf("\nMostrando melhor caminho\n");
    printf("\nTempo total: %d\b", melhor.tempo_total_gasto);
    printf("\nCaminho");
    for (int i = melhor.poisicoes.first; i < melhor.poisicoes.last; i++) {
       Posicao pos = *(Posicao*)melhor.poisicoes.data[i].item;
       printf("\n%d %d", pos.x, pos.y);
    }
    Posicao pos = *(Posicao*)melhor.poisicoes.data[i].item;
    imprimeMapa(mapa, &pos);
    sleep(1);
    clearScreen();
  }

}