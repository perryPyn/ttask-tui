#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

task taskTable[TABLE_LENGTH];

int loadFile() {
  FILE *fptr;

  fptr = fopen("file.txt", "r");
  if (fptr == NULL) {
    printf("CRITICAL: file.txt file failed to open.\n");
    exit(0);
  }
  printf("INFO: The file is now opened.\n");

  int tableIndex = 0;
  printf("INFO: Printing lines read :\n");
  char line[256];

  while (tableIndex < TABLE_LENGTH &&
         fgets(line, sizeof(taskTable[tableIndex].title), fptr) != NULL) {

    printf("%s", line);
    taskTable[tableIndex].isDone = line[3] == 'x';
    strncpy(taskTable[tableIndex].title, &line[6], TITLE_LENGTH);
    taskTable[tableIndex].title[strcspn(taskTable[tableIndex].title, "\r\n")] =
        '\0';

    tableIndex++;
  }

  fclose(fptr);
  printf("INFO: The file is now closed, read %d lines\n", tableIndex);
  return tableIndex;
}

void writeFile(int taskLength) {
  FILE *fptr;

  fptr = fopen("file.txt", "w");
  if (fptr == NULL) {
    printf("CRITICAL: file.txt file failed to open.\n");
    exit(0);
  }
  printf("INFO: The file is ready for rewriting.\n");

  for (int i = 0; i < taskLength; i++) {
    fprintf(fptr, "- [%c] %s\n", taskTable[i].isDone ? 'x' : ' ', taskTable[i].title);
  }
  fclose(fptr);
  printf("INFO: Closing rewritten file.");
}

void printTaskTable(int taskLength) {
  printf("INFO: Printing taskTable :\n");
  for (int i = 0; i < taskLength; i++) {
    printf("[%i]", taskTable[i].isDone);
    printf(" | ");
    printf("[%s]", taskTable[i].title);
    printf("\r\n");
  }
}
