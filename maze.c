#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "maze.h"
#include "tree.h"

// Definições de Maze

Maze *createMaze(int numRows, int numCols) {
  Maze *maze = (Maze *)malloc(sizeof(Maze));

  if (maze) {
    maze->maze = (char **)malloc(numRows * sizeof(char *));
    maze->visited = (bool **)malloc(numRows * sizeof(bool *));
    
    for (int i = 0; i < numRows; i++)
    {
      maze->maze[i] = (char *)malloc(numCols * sizeof(char));
      maze->visited[i] = (bool *)malloc(numCols * sizeof(bool));

      for (int j = 0; j < numCols; j++)
        maze->visited[i][j] = false;      
    }

    maze->size_row = numRows;
    maze->size_col = numCols;
    maze->exit.row = numRows-2;
    maze->exit.col = numCols-1;

    maze->Mouse = 'M';
  }

  else {
    printf("Erro: Falha na alocação de memória.\n");
    exit(EXIT_FAILURE);
  }

  return maze;
}

void printMaze(Maze *maze) {
  for (int i = 0; i < maze->size_row; i++) {
    for (int j = 0; j < maze->size_col; j++) {
        printf("%c", maze->maze[i][j]);
    }
    printf("\n");
  }
}

// Adiciona pontos no labirinto com base na rota 
void insertPointsRouteInMaze(Maze *maze, Route *finalRoute){
  for(int i = 0; i < finalRoute->length; i++){
    maze->maze[finalRoute->positions[i].row][finalRoute->positions[i].col] = '.';
  }
  maze->maze[maze->begin.row][maze->begin.col] = 'M';
  printMaze(maze);
}

// Leitura por terminal
void readMaze(Maze *maze) {
  scanf("%c", &maze->flag);

  for (int i = 0; i < maze->size_row; i++)
  {
    scanf("\n");
    for (int j = 0; j < maze->size_col; j++){
      scanf("%c", &maze->maze[i][j]);  
      if(maze->maze[i][j] == 'M'){
        maze->begin.row = i;
        maze->begin.col = j;
      }
    }  
  }
}

void freeMaze(Maze *maze) {
    if (maze == NULL) {
        return;
    }

    for (int i = 0; i < maze->size_row; i++) {
        free(maze->maze[i]);
        free(maze->visited[i]);
    }

    free(maze->maze);
    free(maze->visited);
    free(maze);
}

// Definições de Route
Route *createRoute() {
  Route *route = (Route *)malloc(sizeof(Route));

  if (route) {
    route->positions = NULL;
    route->length = 0;
    route->isFirstRout = true;
  }

  else {
    printf("Erro: Falha na alocação de memória.\n");
    exit(EXIT_FAILURE);
  }

  return route;
}

/* Adiciona posicoes em uma rota */
void addPosition(Route *route, Position pos, int indexToAdd) {
  route->length++;
  //Realoca tamanho do vetor para nova posicao com base no tamanho da rota
  route->positions = (Position *)realloc(route->positions, route->length * sizeof(Position));
  //Adiciona posicao o index informado
  route->positions[indexToAdd] = pos;
  //Indica que nao e a primeira rota
  route->isFirstRout = false;
}

/* Remove posicoes em uma rota */
void removePosition(Route *route) {
  if (route == NULL || route->length <= 0) {
        return; // Verificação básica de entrada inválida
    }

    if (route->length == 1) {
        free(route->positions); // Se só houver uma posição, libere o array
        route->positions = NULL;
        route->length = 0;
    } else {
        // Cria um novo array de posições o tamanho reduzido
        Position *newPositions = (Position *)malloc((route->length - 1) * sizeof(Position));
        
        // Copia as posições do array original para o novo array
        for (int i = 0; i < route->length - 1; i++) {
            newPositions[i] = route->positions[i];
        }
        free(route->positions);
        // Rota recebe as novas posicoes
        route->positions = newPositions;
        route->length--;
    }
}

/* Copia posicoes para a rota */
void copyPositions(Route *send, Route *receive, int length){
  for(int i = 0; i < length; i++){
    addPosition(receive, send->positions[i], i);
  }
}

/* Copia a rota auxiliar (send) para outra rota (receive) */
void copyRoute(Route *send, Route *receive, int length){
  copyPositions(send, receive, length);
  receive->length = length;
  receive->isFirstRout = false;
}

void freeRoute(Route *route) {
  free(route->positions);
  free(route);
}