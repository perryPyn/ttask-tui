#ifndef APP_H
#define APP_H

#include "task.h"
#include "node.h"

typedef struct {
  Task taskTable[TABLE_LENGTH];
  Node *head;
  int taskLength;
  int isRunning;
  int cursorLine;
} AppState;

#endif // !APP_H
