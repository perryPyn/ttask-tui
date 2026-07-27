#ifndef FILE_H
#define FILE_H

#include "task.h"

int loadFile(Task taskTable[TABLE_LENGTH]);
void printTaskTable(Task taskTable[TABLE_LENGTH], int taskLength);
void writeFile(Task taskTable[TABLE_LENGTH], int taskLength);

#endif // !FILE_H
