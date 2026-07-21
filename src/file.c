#include "file.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>

FILE *fptr;
char title[128];

void loadFile() {
  fptr = fopen("file.txt", "r+");
  if (fptr == NULL) {
    printf("file.txt file failed to open.");
    exit(0);
  } else {
    printf("The file is now opened.\n");

    while (fgets(title, 50, fptr) != NULL) {
      printf("%s", title);
    }
  }
  fclose(fptr);
}
