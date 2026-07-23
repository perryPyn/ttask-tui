#ifndef TASK_H
#define TASK_H

#define TITLE_LENGTH 128
#define TABLE_LENGTH 256

typedef struct {
  int isDone;
  char title[TITLE_LENGTH];
  // char description[512];
} task;

void toggleTaskStatus(task taskTable[TABLE_LENGTH], int lineNumber);
void addTask(task taskTable[TABLE_LENGTH], int lineNumber, int *taskLength);

#endif // !TASK_H
