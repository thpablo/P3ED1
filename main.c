#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include "maze.h"

#define TAM_MAX INT_MAX

void timeProcess(char *go){
  clock_t start = 0, end = 0;
  double cpu_time_used = 0.0;

  if (strcmp(go, "start") == 0)
    start = clock();

  else {
    /* Apresenta tempo de operacao */
    end = clock(); // Marca o tempo final
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Calcula o tempo de CPU utilizado
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
  }
}

int main() {
  // Dimensoes do Labirinto criacao do labirinto
  int numRows, numCols;
  scanf("%d %d", &numRows, &numCols);

  char flag = ' ';  //Flag para escolha do maior ou menor caminho
  scanf(" %c", &flag);

  // timeProcess("start");

  start(numRows, numCols, flag);

  // timeProcess("");

  return 0;
}