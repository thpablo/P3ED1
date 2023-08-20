#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "maze.h"
#include "tree.h"
#include "levels.h"

#define TAM_MAX INT_MAX

void timeProcess(){
  clock_t start, end;
  double cpu_time_used;
  start = clock();
  /* Apresenta tempo de operacao */
  end = clock(); // Marca o tempo final
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Calcula o tempo de CPU utilizado
  printf("Tempo de execução: %f segundos\n", cpu_time_used);
}

int main() {
  /* Dimensoes do Labirinto criacao do labirinto */
  int x, y;
  scanf("%d %d", &x, &y);
  char flag = ' ';  //Flag para escolha do maior ou menor caminho
  scanf(" %c", &flag);

  Maze *maze = createMaze(x, y);
  readMaze(maze);

  /* Criar posicoes que ira simular o rato */
  Position mouse;
  mouse.col = maze->begin.col;
  mouse.row = maze->begin.row;

  /* Alocacao da arvore e insercao da primeira posicao (M) */
  Node *arvore = createNode(maze->begin, 0);
  int highestSizeBranch = 0;

  /* Busca do caminho */
  find(maze, arvore, mouse, arvore->sizeCurrentBranch, &highestSizeBranch, &(arvore->hasExit));
  highestSizeBranch += 2;
  /* Criacao das duas rotas, auxiliar e rotaFinal */
  Route *routeAux = createRoute();
  Route *finalRoute = createRoute();

  /* Criacao Levels */
  Levels *listLevels = initLevels(highestSizeBranch);

  /* Se houver saida, apresenta rota final...*/
  if(arvore->hasExit){
    /*  Percorre a arvore e estabelece o caminho final com base na flag 
        Caminhamento em pre Ordem */
    treeWalking(arvore, flag, 1, routeAux, finalRoute, listLevels);
    /* Insere os pontos no labirinto e mostra trajeto final */
    /* Apresenta tamanho da rota - 1, pois M esta na rota   */
    /* mas nao e considerado como parte do caminho          */
    if(flag == 'f')
      printLevels(listLevels->listPositions, highestSizeBranch);
    else{
      printf("%d\n", finalRoute->length - 1);
      insertPointsRouteInMaze(maze, finalRoute);
    }
  }
  else  /* Caso nao tenha saida */
    printf("EPIC FAIL!\n"); 
  
  /* Libera alocacoes */
  freeLevels(listLevels);
  freeRoute(routeAux);
  freeRoute(finalRoute);
  freeMaze(maze);
  freeTree(arvore);

  //timeProcess();

  return 0;
}