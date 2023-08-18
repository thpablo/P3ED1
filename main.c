#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "maze.h"
#include "tree.h"

#define TAM_MAX INT_MAX

int main() {
  /* Marcar tempo de operacao do programa */
  clock_t start, end;
  double cpu_time_used;
  start = clock();

  /* Dimensoes do Labirinto criacao do labirinto */
  int x, y;
  scanf("%d %d", &x, &y);
  char flag;  //Flag para escolha do maior ou menor caminho
  scanf(" %c", &flag);
  Maze *maze = createMaze(x, y);
  readMaze(maze);

  /* Criar posicoes que ira simular o rato */
  Position mouse;
  mouse.col = maze->begin.col;
  mouse.row = maze->begin.row;

  /* Alocacao da arvore e insercao da primeira posicao (M) */
  Node *arvore;
  arvore = insertNode(mouse, 1);

  /* Busca do caminho */
  find(maze, arvore, mouse, arvore->sizeCurrentBranch + 1, &(arvore->hasExit));

  /* Criacao das duas rotas, auxiliar e rotaFinal */
  Route *routeAux = createRoute();
  Route *finalRoute = createRoute();

  /* Se houver saida, apresenta rota final...*/
  if(arvore->hasExit){
    /* Percorre a arvore e estabelece o caminho final com base na flag */
    preOrdem(arvore, flag, arvore->sizeCurrentBranch, routeAux, finalRoute);
    printf("Rota final:\n");
    printRoute(finalRoute);
    insertPointsRouteInMaze(maze, finalRoute);
  }
  else  /* Caso nao tenha saida */
    printf("EPIC FAIL\n"); 
  
  /* Libera alocacoes */
  freeRoute(routeAux);
  freeRoute(finalRoute);


  /* Apresenta tempo de operacao */
  end = clock(); // Marca o tempo final
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Calcula o tempo de CPU utilizado
  printf("Tempo de execução: %f segundos\n", cpu_time_used);

  return 0;
}