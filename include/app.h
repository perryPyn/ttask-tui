#ifndef APP_H
#define APP_H

#include "node.h"
#include <ncurses.h>

typedef struct {
  Node *head;
  Node *currentNode;
  int taskLength;
  int isRunning;
  int cursorLine;
  WINDOW *sidebarWin;
  WINDOW *tasksWin;
} AppState;

#endif // !APP_H
