#include <stdio.h>
#include <stdlib.h>

#include "maze.h"
#include "tree.h"
#include "levels.h"

/* Inicia lista de Posicoes */
ListPositions *initList(int size){
    ListPositions *newListPositions  = (ListPositions *) malloc(size * sizeof(ListPositions));
    for(int i = 0; i < size; i++)
        newListPositions[i].hasPosition = false;
    return newListPositions;
}
/* Inicia estrutura que armazena lista de posicoes por level */
Levels *initLevels(int size){
    Levels *newLevel = (Levels *) malloc(sizeof(Levels));
    newLevel->listPositions = initList(size);
    newLevel->size = size;

    return newLevel;
}
/* Cria nova lista de posicoes para posicoes a mais em um nivel (Lista Encadeada) */
ListPositions* createListPositions(){
    ListPositions *newListPositions = (ListPositions *) malloc(sizeof(ListPositions));
    newListPositions->hasPosition = false;
    newListPositions->next = NULL;
    return newListPositions;
}

// Função para desalocar uma lista de posições
void freeListPositions(ListPositions *list, int size) {
    for (int i = 1; i < size; i++) {
        ListPositions *current = &list[i];
        current = current->next;
        while (current != NULL) {
            ListPositions *next = current->next;
            free(current);
            current = next;
        }
    }
    free(list);
}
// Função para desalocar a estrutura Levels
void freeLevels(Levels *levels) {
    if (levels == NULL) {
        return;
    }

    freeListPositions(levels->listPositions, levels->size);
    free(levels);
}

/* Insere as posicoes na lista de Posicoes de cada Level */
void insertInListLevels(Levels* levels, Position position, int index){
    /*Se ja haver posicoes no mesmo level, insere na ultima posicao da lista encadeada */
    if(levels->listPositions[index].hasPosition){
        levels->listPositions[index].pLastPosition->next = createListPositions();
        levels->listPositions[index].pLastPosition = levels->listPositions[index].pLastPosition->next;
        levels->listPositions[index].pLastPosition->next = NULL;
        levels->listPositions[index].pLastPosition->positions = position;
    } else {
        levels->listPositions[index].positions = position;
        levels->listPositions[index].next = NULL;
        levels->listPositions[index].pLastPosition = &(levels->listPositions[index]);
        levels->listPositions[index].hasPosition = true;
    }
}
/* Printa as outras posicoes no mesmo level (Lista Encadeada) */
void printOthersPositionsInLevel(ListPositions *listPositions){
    while (listPositions != NULL) {
        printf("(%d, %d) " , listPositions->positions.row, listPositions->positions.col);
        listPositions = listPositions->next;
    }
}

/* Função para printar posicoes por level */
void printLevels(ListPositions* listPositions, int size){
    for(int i = 1; i < size; i++){
        printf("Nivel %d:\n (%d, %d) ", i, listPositions[i].positions.row, listPositions[i].positions.col);
        if(listPositions[i].next != NULL)
            printOthersPositionsInLevel(listPositions[i].next);
        printf("\n");
    }
}

