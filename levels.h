#ifndef LEVELS_H
#define LEVELS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "maze.h"

typedef struct list{
    Position positions;
    struct list* next;
    struct list* pLastPosition;
    bool hasPosition;
} ListPositions;

typedef struct {
    ListPositions *listPositions;
    int size;
} Levels;


Levels *initLevels(int size);
ListPositions *initList(int size);
void insertInListLevels(Levels* levels, Position position, int index);
void printLevels(ListPositions* listPosition, int size);

#endif //   LEVELS_H