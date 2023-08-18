#include <stdlib.h>

#include "tree.h"
#include "maze.h"


void initTree(Node **pRoot){
    *pRoot = NULL;
    (*pRoot)->hasExit = false;
}

Node *createNode(Position newPosition, int currentSize){
    Node *newNode = (Node*) malloc(sizeof(Node));
    if(newNode == NULL){
        printf("Erro ao alocar Nó\n");
        return NULL;
    }
    newNode->posNode = newPosition;
    newNode->down = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->up = NULL;
    newNode->sizeCurrentBranch = currentSize;
    return newNode;
}

Node * insertNode(Position newPosition, int currentSize){
    Node *currentNode = createNode(newPosition, currentSize);
    currentNode->isExit = false;
    return currentNode;
}

void popNode(Node **pos){
    if(*pos == NULL){
        printf("Não foi possível desalocar, ponteiro nulo\n");
        return;
    }
    
    free((*pos));
    *pos = NULL;
}


int isValidPosition(Position newPosition, Maze *maze){
  if (newPosition.col < 0 || newPosition.row < 0 ||
      newPosition.col >= maze->size_col || newPosition.row >= maze->size_row) {
    // A posição está fora dos limites do labirinto.
    return 0;
  }
  if (maze->maze[newPosition.row][newPosition.col] == '*' ||
      maze->maze[newPosition.row][newPosition.col] == '#' ||
      maze->visited[newPosition.row][newPosition.col] == true ){
    // A posição contém uma parede / local visitado.
    return 0;
  }
  
  return 1;
}


void find(Maze *maze, struct node *noAtual, Position mousePos, int currentSize, bool *hasExit){
  struct node *noUsado;
  //Caso Base
  if(mousePos.col == maze->exit.col && mousePos.row == maze->exit.row){
    noAtual->isExit = true; // O no é uma saida
    *hasExit = true;        // O labirinto contem uma saida
    return;
  }
  //Marca posicao como visitada
  maze->visited[mousePos.row][mousePos.col] = true;

  Position actions[4] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

  for(int i = 0; i < 4; i++){
    Position newPosition = {mousePos.row + actions[i].row, mousePos.col + actions[i].col};  
    if(isValidPosition(newPosition, maze)){
        switch (i) {  
          case 0: //Direita
            noAtual->right = insertNode(newPosition, currentSize);
            noUsado = noAtual->right;
            find(maze, noUsado, newPosition, currentSize + 1, hasExit);
            break;
          case 1: //Baixo
            noAtual->down = insertNode(newPosition, currentSize);            
            noUsado = noAtual->down;
            find(maze, noUsado, newPosition, currentSize + 1, hasExit);

            break;
          case 2: //Esquerda
            noAtual->left = insertNode(newPosition, currentSize);
            noUsado = noAtual->left;
            find(maze, noUsado, newPosition, currentSize + 1, hasExit);
            break;
          case 3: //Cima
            noAtual->up = insertNode(newPosition, currentSize);
            noUsado = noAtual->up;
            find(maze, noUsado, newPosition, currentSize + 1, hasExit);
            break;
        }
    }    
  }
  //Desmarca posicao como visitada
  maze->visited[mousePos.row][mousePos.col] = false;
  return;
}

void printRoute(Route *rota){
  for(int i = 0; i < rota->length; i++){
    printf("r: %d, c: %d\n", rota->positions[i].row, rota->positions[i].col);
  }
}

void copyPositions(Route *send, Route *receive, int length){
  for(int i = 0; i < length; i++){
    addPosition(receive, send->positions[i]);
  }
}

void copyRoute(Route *send, Route *receive, int length){
  copyPositions(send, receive, length);
  receive->length = length;
  receive->isFirstRout = false;
  //printf("S: level: %d, Atual length: %d  Final length: %d isFirst: %d\n", level, rotaAtual->length, rotaFinal->length, rotaFinal->isFirstRout);
}

void preOrdem(Node *pRoot, char flag, int lengthRoute, Route *rotaAtual, Route *rotaFinal){
  if(pRoot == NULL){
    return;
  }
  addPosition(rotaAtual, pRoot->posNode); //Adiciona rota no RotaAtual

  // Se o no e a saida
  if(pRoot->isExit){
    switch(flag){
      case 's': //Menor Caminho
        //Caso seja a primeira rota ou o tamanho do caminho < tamanho da rota final
        if(rotaFinal->isFirstRout || lengthRoute < rotaFinal->length)
           copyRoute(rotaAtual, rotaFinal, lengthRoute);
      break;
      case 'g': //Maior  caminho
        if(rotaFinal->isFirstRout || rotaFinal->length < lengthRoute)
          copyRoute(rotaAtual, rotaFinal, lengthRoute);
      break;
    }
  }
  preOrdem(pRoot->right, flag, pRoot->sizeCurrentBranch + 1, rotaAtual, rotaFinal);
  preOrdem(pRoot->down, flag, pRoot->sizeCurrentBranch + 1, rotaAtual, rotaFinal);
  preOrdem(pRoot->left, flag, pRoot->sizeCurrentBranch + 1, rotaAtual, rotaFinal);
  preOrdem(pRoot->up, flag, pRoot->sizeCurrentBranch + 1, rotaAtual, rotaFinal);

  removePosition(rotaAtual, lengthRoute - 1);
  
}