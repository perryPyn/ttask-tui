#ifndef APP_H
#define APP_H

#include "task.h"

typedef struct {
  task taskTable[TABLE_LENGTH];
  int taskLength;
  int isRunning;
  int cursorLine;
} AppState;

#endif // !APP_H
