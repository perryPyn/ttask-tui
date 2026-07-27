#include "file.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int loadFile(Task taskTable[TABLE_LENGTH]) {
  FILE *fptr;

  fptr = fopen("file.txt", "r");
  if (fptr == NULL) {
    msgLog("[CRIT] file.txt file failed to open.\n");
    exit(0);
  }
  msgLog("[INFO] The file is now opened.\n");

  int tableIndex = 0;
  msgLog("[INFO] Printing lines read :\n");
  char line[256];

  while (tableIndex < TABLE_LENGTH &&
         fgets(line, sizeof(taskTable[tableIndex].title), fptr) != NULL) {

    msgLog("%s", line);
    taskTable[tableIndex].isDone = line[3] == 'x';
    strncpy(taskTable[tableIndex].title, &line[6], TITLE_LENGTH);
    taskTable[tableIndex].title[strcspn(taskTable[tableIndex].title, "\r\n")] =
        '\0';

    tableIndex++;
  }

  fclose(fptr);
  msgLog("[INFO] The file is now closed, read %d lines\n", tableIndex);
  return tableIndex;
}

void writeFile(Task taskTable[TABLE_LENGTH], int taskLength) {
  FILE *fptr;

  fptr = fopen("file.txt", "w");
  if (fptr == NULL) {
    msgLog("[CRIT] file.txt file failed to open.\n");
    exit(0);
  }
  msgLog("[INFO] The file is ready for rewriting\n");

  for (int i = 0; i < taskLength; i++) {
    fprintf(fptr, "- [%c] %s\n", taskTable[i].isDone ? 'x' : ' ',
            taskTable[i].title);
  }
  fclose(fptr);
  msgLog("[INFO] Closing rewritten file.\n");
}

void printTaskTable(Task taskTable[TABLE_LENGTH], int taskLength) {
  msgLog("[INFO] Printing taskTable :\n");
  for (int i = 0; i < taskLength; i++) {
    msgLog("[%i]", taskTable[i].isDone);
    msgLog(" | ");
    msgLog("[%s]", taskTable[i].title);
    msgLog("\r\n");
  }
}
