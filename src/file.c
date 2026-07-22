#include "file.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

task taskTable[TABLE_LENGTH];

void loadFile() {
  FILE *fptr;

  fptr = fopen("file.txt", "r");
  if (fptr == NULL) {
    printf("CRITICAL: file.txt file failed to open.\n");
    exit(0);
  }
  printf("INFO: The file is now opened.\n");

  int tableIndex = 0;
  printf("INFO: Printing lines read :\n");
  while (tableIndex < TABLE_LENGTH &&
         fgets(taskTable[tableIndex].title, sizeof(taskTable[tableIndex].title),
               fptr) != NULL) {
    printf("%s", taskTable[tableIndex].title);

    tableIndex++;
  }

  fclose(fptr);
  printf("INFO: The file is now closed\n");
}

void printTaskTable() {
  printf("INFO: Printing taskTable :\n");
  for (int i = 0; i < 2; i++) {
    printf("%s", taskTable[i].title);
  }
}
