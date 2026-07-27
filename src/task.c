#include "task.h"
#include <ncurses.h>
#include <string.h>

void toggleTaskStatus(Task taskTable[TABLE_LENGTH], int lineNumber) {
  taskTable[lineNumber].isDone = taskTable[lineNumber].isDone == 0;
}

void addTask(Task taskTable[TABLE_LENGTH], int lineNumber, int *taskLength) {
  char title[TITLE_LENGTH];
  int isTypingTitle = 1;

  echo();
  while (isTypingTitle) {
    getstr(title);
    int ch = getch();
    if (ch == '\n') {
      isTypingTitle = 0;
    }
  }
  noecho();

  taskTable[lineNumber].isDone = 0;
  strcpy(taskTable[lineNumber].title, title);

  // add way to enter title :
  // echo();               // Réactive l'affichage le temps de la saisie
  // getstr(task_title);   // L'utilisateur voit ce qu'il tape
  // noecho();             // On désactive à nouveau

  *taskLength += 1;
}
