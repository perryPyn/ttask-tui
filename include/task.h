#ifndef TASK_H
#define TASK_H

#include "types.h"

void appendTask(TaskData *taskData, int *cursor);
void removeTask(TaskData *taskData, int *cursor);
void moveUp(TaskData *taskData, int *cursor);
void moveDown(TaskData *taskData, int *cursor);
void increaseImportance(TaskData *taskData);
void decreaseImportance(TaskData *taskData);
void renameTask(char title[TITLE_LENGTH]);

#endif // !TASK_H
