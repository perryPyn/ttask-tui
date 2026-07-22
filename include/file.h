#ifndef FILE_H
#define FILE_H

#include "task.h"

int loadFile(task taskTable[TABLE_LENGTH]);
void printTaskTable(task taskTable[TABLE_LENGTH], int taskLength);
void writeFile(task taskTable[TABLE_LENGTH], int taskLength);

#endif // !FILE_H
