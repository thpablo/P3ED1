#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include "maze.h"
#include "levels.h"

typedef struct node{
    struct node *right;
    struct node *down;
    struct node *left;
    struct node *up;
    int sizeCurrentBranch; //Tamanho do galho até o nó atual
    bool isExit;
    bool hasExit;
    Position posNode; // Posição
}Node;


/* Funções da Árvore */
//Inicia
void initTree(Node **pRoot);

//Cria No
Node *createNode(Position newPos, int currentSize);

// Inicia condicoes iniciais do No
Node *insertNode(Position newPosition, int currentSize); //Inicia condicoes iniciais do No

//Funcao recursiva de encontrar caminhos
void find(Maze *maze, struct node *noAtual, Position mousePos, int currentSize, int* highestSizeBranch, bool *);

//Valida posicao
int isValidPosition(Position newPosition, Maze *maze);

// Caminhamento em Pre Ordem para encontrar os caminhos
void treeWalking(Maze *, Node *pRoot, char flag, int lengthRoute, Route *rotaAtual, Route *rotaFinal, Levels *listLevel);

// Printa Rota
void printRoute(Route *, int length);

#endif // TREE_H