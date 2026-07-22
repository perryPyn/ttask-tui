#ifndef FILE_H
#define FILE_H

#define TITLE_LENGTH 128
#define TABLE_LENGTH 256

typedef struct {
  int isDone;
  char title[TITLE_LENGTH];
  // char description[512];
} task;

int loadFile(void);
void printTaskTable(int taskLength);
void writeFile(int taskLength);

#endif // !FILE_H
