#include "task.h"

void toggleTaskStatus(task taskTable[TABLE_LENGTH], int lineNumber){
  taskTable[lineNumber].isDone = taskTable[lineNumber].isDone==0;
}
