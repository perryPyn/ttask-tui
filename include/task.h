#ifndef TASK_H
#define TASK_H

#define TITLE_LENGTH 128
#define TABLE_LENGTH 256

typedef struct {
  // int indentation;
  int status;
  char title[TITLE_LENGTH];
  // char description[512];
} Task;

typedef enum {
    TASK_TODO = 0,
    TASK_IN_PROGRESS,
    TASK_DONE,
    TASK_ON_HOLD,
    TASK_COUNT
} TaskStatus;

#endif // !TASK_H
