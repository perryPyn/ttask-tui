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
  WINDOW *sidebarContent;
  WINDOW *tasksWin;
  WINDOW *tasksContent;
} AppState;

#endif // !APP_H
