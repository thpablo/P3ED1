#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int row, col; // Coordenadas: linha, coluna
} Position;

typedef struct {
    char **maze; // Matriz de caracteres representando o labirinto
    char flag; // Caractere que representa o tipo de saída
    char Mouse; // Caractere 'M' representa o rato
    int size_row, size_col; // Dimensões do labirinto
    Position begin; // Inicío do percurso
    Position exit; // Saída do labirinto
    bool **visited; // Matriz para rastrear as posições visitadas
} Maze;

typedef struct {
    Position *positions;    // Array de posições
    int length;             // Comprimento do caminho
    bool isFirstRout;       //Indica se e a primeira rota para adicionar em Rota Final
} Route;

// Funções do Maze

// Função para alocar memória para um labirinto
Maze *createMaze(int numRows, int numCols);

// Função para inicializar o labirinto;
void readMaze(Maze *maze);

// Função para desalocar memória de um labirinto
void freeMaze(Maze *maze);

// Inicia o processo no labirinto
void start(int numRows, int numCols, char flag);

// Funções do Route

// Insere os pontos no labirinto
void insertPointsRouteInMaze(Maze *maze, Route *finalRoute);

// Função para criar um novo caminho
Route *createRoute();

// Função para adicionar uma posição ao caminho
void addPosition(Route *route, Position pos, int index);

//Funcoes para copiar posicoes e rota 
void copyPositions(Route *send, Route *receive, int length);
void copyRoute(Route *send, Route *receive, int length);

// Função para remover uma posição ao caminho
void removePosition(Route *route);
 
// Função para liberar a memória do caminho
void freeRoute(Route *route);
void printMaze(Maze *);

#endif // MAZE_H