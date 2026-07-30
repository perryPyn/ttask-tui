#ifndef TASK_H
#define TASK_H

#include "types.h"

void appendTask(TaskData *taskData, int *cursor);
void removeTask(TaskData *taskData, int *cursor);
void moveUp(TaskData *taskData, int *cursor);
void moveDown(TaskData *taskData, int *cursor);

#endif // !TASK_H
