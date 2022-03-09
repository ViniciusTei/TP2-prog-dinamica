# TP2 

Utilizando programação dinâmica, fazer um algoritmo que calcule a melhor rota para nosso personagem Samus sair da caverna em segurança. Porém, algumas áreas da caverna são bloqueadas, e outras estão infestadas de monstros que Samus precisa derrotar se quiser escapar.

> Dynamic programming is a fancy name for [recursion] with a table. Instead of solving subproblems recursively, solve them sequentially and store their solutions in a table. The trick is to solve them in the right order so that whenever the solution to a subproblem is needed, it is already available in the table.

> — Ian Parberry, Problems on Algorithms
 

### Pontos importantes

- Samus inicia sempre no fundo da caverna (linha mais abaixo do mapa)
- Samus move apenas para cima, seja para a esquerda ou para a direita
- Samus pode iniciar de qualquer celula inferior, e sair de qualquer ceulua superior
- Cada movimento de Samus gasta t unidades de tempo
- Ao passar por um monstro, Samus gasta t + t' unidades de tempo
- Para sair Samus precisa escapar da lava que sove na caverna com uma velocidade L
- O tempo total gasto por Samus deve ser menor que L x h, sendo h a altura da caverna

### To Do

 - [x] Criar estrutura do personagem (Samus e monstros)
   - [x] Cada personagem deve ter um identficador unico, e um t associado
 - [x] Criar estrutura do mapa
 - [x] Criar estrutura de movimentação
   - [x] Fazer uma função que percorra por todos os caminhos e armazenas os caminhos válidos em uma tabela de soluções
   - [x] Testar os caminhos armazenados como soluções para encontrar o melhor deles
   - [x] Para movimentar, a regra eh que podemos ir apenas para cima, esquerda ou direita.
     - se o y é 0 pode andar pra cima e para direita
     - se o y é L - 1 pode andar pra cima epara esquerda
     - se x é par pode andar pra cima e pra direira
     - se o x é impar pode andar pra cima e para esquerda
 - [x] Criar leitura de arquivos
 - [ ] Faze extras do trabalho
   - [x] Explicar e usar algum algoritmo para detectar células livres, porém inalcançáveis, antes da aplicação da programação dinâmica.
   - [ ] Plotar gráficos de desempenho de tempo do algoritmo para diferentes tamanhos de entrada, definidos pelo grupo.
   - [x] Melhorar a interface do programa, mostrando de forma gráfica o melhor caminho.
   - [ ] Criar um programa à parte para geração de arquivos de entrada, de preferência com alguns parâmetros para orientar a geração.
