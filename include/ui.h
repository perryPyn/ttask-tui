#ifndef UI_H
#define UI_H

#include "task.h"

void initUI(void);
void displayTaskTable(Task taskTable[TABLE_LENGTH], int taskLength,
                      int cursorLine);

#endif // !UI_H
