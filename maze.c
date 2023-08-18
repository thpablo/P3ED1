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
  for (int i = 0; i < maze->size_row; i++)
    free(maze->maze[i]);

  free(maze->maze);
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
void addPosition(Route *route, Position pos) {
  route->length++;
  route->positions = (Position *)realloc(route->positions, route->length * sizeof(Position));
  route->positions[route->length - 1] = pos;
  route->isFirstRout = false;
}

/* Remove posicoes em uma rota */
void removePosition(Route *route, int indexToRemove) {
    if (indexToRemove < 0 || indexToRemove >= route->length) {
        // Índice inválido, não há nada para remover
        return;
    }
    // Deslocar elementos para preencher a posição que será removida
    for (int i = indexToRemove; i < route->length - 1; i++) {
        route->positions[i] = route->positions[i + 1];
    }
    // Diminuir o comprimento da rota
    route->length--;

    // Redimensionar o array de posições
    route->positions = (Position *)realloc(route->positions, route->length * sizeof(Position));
}

void freeRoute(Route *route) {
  free(route->positions);
  free(route);
}