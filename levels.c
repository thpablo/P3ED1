#include <stdio.h>
#include <stdlib.h>

#include "maze.h"
#include "tree.h"
#include "levels.h"

ListPositions *initList(int size){
    ListPositions *newListPositions  = (ListPositions *) malloc(size * sizeof(ListPositions));
    for(int i = 0; i < size; i++)
        newListPositions[i].hasPosition = false;
    return newListPositions;
}

Levels *initLevels(int size){
    Levels *newLevel = (Levels *) malloc(sizeof(Levels));
    newLevel->listPositions = initList(size);
    newLevel->size = size;

    return newLevel;
}
ListPositions* createListPositions(){
    ListPositions *newListPositions = (ListPositions *) malloc(sizeof(ListPositions));
    newListPositions->hasPosition = false;
    newListPositions->next = NULL;
    return newListPositions;
}

void freeListPositions(ListPositions* head) {
    while (head != NULL) {
        ListPositions* temp = head;
        head = head->next;
        free(temp);
    }
}

void insertInListLevels(Levels* levels, Position position, int index){
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
void printOthersPositionsInLevel(ListPositions *listPositions){
    while (listPositions != NULL) {
        printf("(%d, %d) " , listPositions->positions.row, listPositions->positions.col);
        listPositions = listPositions->next;
    }
}

void printLevels(ListPositions* listPositions, int size){
    for(int i = 1; i < size; i++){
        printf("Nivel %d:\n (%d, %d) ", i, listPositions[i].positions.row, listPositions[i].positions.col);
        if(listPositions[i].next != NULL)
            printOthersPositionsInLevel(listPositions[i].next);
        printf("\n");
    }
}

