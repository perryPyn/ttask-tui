#include "file.h"
#include "log.h"
#include "node.h"
#include "types.h"
#include "utils.h"
#include "workspaceNode.h"
#include <ncurses.h>
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

int loadFile(WorkspaceData *workspaceData, char *filePath) {
  FILE *fptr = fopen(filePath, "r");
  if (fptr == NULL) {
    msgLog("[CRIT] Failed to open task.md at %s\n", filePath);
    return 0;
  }
  msgLog("[INFO] Opened task.md at %s\n", filePath);

  char line[256];
  int linesRead = 0;
  WorkspaceNode *currentWorkspace = workspaceData->headWorkspace;
  Node *previousNode =
      currentWorkspace ? currentWorkspace->taskData.head : NULL;
  bool isFirstWorkspace = true;

  while (fgets(line, sizeof(line), fptr) != NULL) {
    linesRead++;
    line[strcspn(line, "\r\n")] = '\0';

    if (line[0] == '#') {
      char name[NAME_LENGTH];
      sscanf(line, "# %" STR(MAX_NAME_LENGTH) "[^\n]", name);

      if (isFirstWorkspace && currentWorkspace != NULL) {
        strcpy(currentWorkspace->name, name);
        isFirstWorkspace = false;
      } else {
        Node *newHead = createNode(&(Task){0, 0, 0, "Head"});
        TaskData taskData = {newHead, NULL, 0};
        currentWorkspace =
            appendWorkspaceNode(name, &taskData, currentWorkspace);
        workspaceData->length++;
        previousNode = newHead;
      }
    } else {
      int indentation = 0;
      int importance;
      char statusChar;
      char title[TITLE_LENGTH];

      if (sscanf(line, " %n- [%c] %" STR(MAX_TITLE_LENGTH) "[^|] | %d",
                 &indentation, &statusChar, title, &importance) == 3) { // /!\ ==3 bc %n does not count

        size_t len = strlen(title);
        while (len > 0 && title[len - 1] == ' ') {
          title[--len] = '\0';
        }

        Task task = {indentation, statusFromChar(statusChar), importance, ""};
        cpyStr(task.title, title, TITLE_LENGTH);

        previousNode = appendNode(&task, previousNode);

        if (currentWorkspace) {
          currentWorkspace->taskData.length++;
        }
      }
    }
  }

  fclose(fptr);

  WorkspaceNode *ws = workspaceData->headWorkspace;
  while (ws != NULL) {
    ws->taskData.currentNode = ws->taskData.head->next;
    ws = ws->next;
  }

  return linesRead;
}

void writeFile(WorkspaceNode *WorkspaceHead, char *filePath) {
  if (WorkspaceHead == NULL) {
    msgLog("[WARN] No workspaces to save.\n");
    return;
  }
  FILE *fptr;

  fptr = fopen(filePath, "w");
  if (fptr == NULL) {
    msgLog("[CRIT] File failed to open at %s\n", filePath);
    exit(0);
  }
  // msgLog("[INFO] The file is ready for rewriting\n");

  WorkspaceNode *workspaceNode = WorkspaceHead;
  while (workspaceNode != NULL) {
    fprintf(fptr, "# %s\n", workspaceNode->name);
    Node *node = workspaceNode->taskData.head;
    while (node->next != NULL) {
      node = node->next; // At the start to skip head
      fprintf(fptr, "%*s- [%s] %s | %d\n", node->task.indentation, "",
              STATUS_SYMBOLS[node->task.status], node->task.title,
              node->task.importance);
    }
    workspaceNode = workspaceNode->next; // At the end to not skip Default
  }

  fclose(fptr);
  // msgLog("[INFO] Rewritten file at %s\n", filePath);
}

void printTaskTable(Node *head) {
  msgLog("[INFO] Printing taskTable :\n");
  Node *node = head;
  while (node->next != NULL) {
    node = node->next;
    msgLog("\t[%d] | [%s]\n", node->task.status, node->task.title);
  }
}
