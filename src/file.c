#include "file.h"
#include "log.h"
#include "node.h"
#include "task.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int loadFile(Node *head) {
  FILE *fptr;

  fptr = fopen("file.txt", "r");
  if (fptr == NULL) {
    msgLog("[CRIT] file.txt file failed to open.\n");
    exit(0);
  }
  msgLog("[INFO] The file is now opened.\n");

  msgLog("[INFO] Printing lines read :\n");
  char line[256];

  int i = 0;
  for (; fgets(line, TITLE_LENGTH, fptr) != NULL; i++) {
    msgLog("   %s", line);
    line[strcspn(line, "\r\n")] = '\0';

    // Checking the indentation
    // ...

    // Creating the node
    Task task = {line[3] == 'x', ""};
    cpyStr(task.title, &line[6]);
    addNodeAtIndex(&task, head, i);
  }

  fclose(fptr);
  msgLog("[INFO] The file is now closed, read %d lines\n", i);
  return i;
}

void writeFile(Node *head, int taskLength) {
  FILE *fptr;

  fptr = fopen("file.txt", "w");
  if (fptr == NULL) {
    msgLog("[CRIT] file.txt file failed to open.\n");
    exit(0);
  }
  msgLog("[INFO] The file is ready for rewriting\n");

  Node *node = head;
  while (node->next != NULL) {
    node = node->next;
    

    fprintf(fptr, "- [%c] %s\n", node->task.status ? 'x' : ' ',
            node->task.title);
  }

  fclose(fptr);
  msgLog("[INFO] Closing rewritten file.\n");
}

void printTaskTable(Node *head, int taskLength) {
  msgLog("[INFO] Printing taskTable :\n");
  Node *node = head;
  while (node->next != NULL) {
    node = node->next;
    msgLog("[%d] | [%s]\n", node->task.status, node->task.title);
  }
}
