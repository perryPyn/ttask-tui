#ifndef APP_H
#define APP_H

#include "node.h"

typedef struct {
  Node *head;
  Node *currentNode;
  int taskLength;
  int isRunning;
  int cursorLine;
} AppState;

#endif // !APP_H
