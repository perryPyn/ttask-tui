#include "file.h"
#include "log.h"
#include "node.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *STATUS_SYMBOLS[TASK_COUNT] = {[TASK_TODO] = " ",
                                                 [TASK_IN_PROGRESS] = "-",
                                                 [TASK_DONE] = "x",
                                                 [TASK_ON_HOLD] = "~"};

static TaskStatus statusFromChar(char c) {
  for (int i = 0; i < TASK_COUNT; i++) {
    if (STATUS_SYMBOLS[i][0] == c) {
      return (TaskStatus)i;
    }
  }
  return TASK_TODO;
}

int loadFile(Node *head) {
  FILE *fptr;

  fptr = fopen("file.md", "r");
  if (fptr == NULL) {
    msgLog("[CRIT] file.md file failed to open.\n");
    exit(0);
  }
  msgLog("[INFO] The file is now opened.\n");

  msgLog("[INFO] Printing lines read :\n");
  char line[256];

  int i = 0;
  Node *previousNode = head;
  for (; fgets(line, TITLE_LENGTH, fptr) != NULL; i++) {
    msgLog("\t%s", line);
    line[strcspn(line, "\r\n")] = '\0';

    // Checking the indentation
    int indentation = 0;
    while (line[indentation] == ' ') {
      indentation++;
    }

    // Creating the node
    Task task = {indentation, statusFromChar(line[3 + indentation]), ""};
    cpyStr(task.title, &line[6 + indentation]);
    previousNode = appendNode(&task, previousNode);
  }

  fclose(fptr);
  msgLog("[INFO] The file is now closed, read %d lines\n", i);
  return i;
}

void writeFile(Node *head) {
  FILE *fptr;

  fptr = fopen("file.md", "w");
  if (fptr == NULL) {
    msgLog("[CRIT] file.md file failed to open.\n");
    exit(0);
  }
  msgLog("[INFO] The file is ready for rewriting\n");

  Node *node = head;
  while (node->next != NULL) {
    node = node->next;
    fprintf(fptr, "%*s- [%s] %s\n", node->task.indentation, "",
            STATUS_SYMBOLS[node->task.status], node->task.title);
  }

  fclose(fptr);
  msgLog("[INFO] Closing rewritten file.\n");
}

void printTaskTable(Node *head) {
  msgLog("[INFO] Printing taskTable :\n");
  Node *node = head;
  while (node->next != NULL) {
    node = node->next;
    msgLog("\t[%d] | [%s]\n", node->task.status, node->task.title);
  }
}
