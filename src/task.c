#include "task.h"
#include <string.h>

void toggleTaskStatus(task taskTable[TABLE_LENGTH], int lineNumber) {
  taskTable[lineNumber].isDone = taskTable[lineNumber].isDone == 0;
}

void addTask(task taskTable[TABLE_LENGTH], int lineNumber, int *taskLength) {
  taskTable[lineNumber].isDone = 0;
  strcpy(taskTable[lineNumber].title, "dummy title");

  // add way to enter title :
  // echo();               // Réactive l'affichage le temps de la saisie
  // getstr(task_title);   // L'utilisateur voit ce qu'il tape
  // noecho();             // On désactive à nouveau

  *taskLength += 1;
}
