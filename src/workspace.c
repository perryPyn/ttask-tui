#include "workspace.h"
#include "log.h"
#include "node.h"
#include "types.h"
#include "utils.h"
#include "workspaceNode.h"
#include <ncurses.h>
#include <stdio.h>

void appendWorkspace(WorkspaceData *workspaceData, int *cursor) {
  if (workspaceData == NULL) return;

  char name[NAME_LENGTH] = "";
  if (!promptString("New Workspace", name, NAME_LENGTH)) {
    return;
  }

  Node *newHead = createNode(&(Task){0, 0, 0, "Head"});
  if (newHead == NULL) return;

  TaskData taskData = {
      .head = newHead,
      .currentNode = NULL,
      .length = 0
  };

  addWorkspaceNode(name, &taskData, workspaceData->currentWorkspace);

  workspaceData->length++;
  if (cursor) (*cursor)++;

  if (workspaceData->currentWorkspace != NULL) {
    workspaceData->currentWorkspace = workspaceData->currentWorkspace->next;
  }
}

void removeWorkspace(WorkspaceData *workspaceData, int *cursor) {
  if (workspaceData->currentWorkspace == NULL) {
    msgLog("[WARN] current workspace is NULL");
    return;
  }
  WorkspaceNode *toDelete = workspaceData->currentWorkspace;

  if (toDelete->previous != NULL) { // Usual case
    workspaceData->currentWorkspace = toDelete->previous;
    workspaceData->length -= 1;
    (*cursor)--;
  } else if (toDelete->next != NULL) { // If it is the fisrt one
    workspaceData->currentWorkspace = toDelete->next;
    workspaceData->headWorkspace = toDelete->next;
    workspaceData->length -= 1;
  } else { // If workspace to delete is the last one, we create default
    TaskData taskData = {.head = createNode(&(Task){0, 0, 0, "Head"}),
                         .currentNode = NULL,
                         .length = 0};

    workspaceData->headWorkspace = createWorkspace("Default", &taskData);
    workspaceData->currentWorkspace = workspaceData->headWorkspace;
    workspaceData->length = 1; // Just to be sure be shoud not be necessary
  }

  removeWorkspaceNode(toDelete);
}

void moveUpWorkspace(WorkspaceData *workspaceData, int *cursor) {
  if (workspaceData->currentWorkspace == NULL) {
    return;
  }
  if (workspaceData->currentWorkspace->previous != NULL) {
    workspaceData->currentWorkspace = workspaceData->currentWorkspace->previous;
    (*cursor)--;
  }
}

void moveDownWorkspace(WorkspaceData *workspaceData, int *cursor) {
  if (workspaceData->currentWorkspace == NULL) {
    return;
  }
  if (*cursor < workspaceData->length) {
  }
  if (workspaceData->currentWorkspace->next != NULL) {
    workspaceData->currentWorkspace = workspaceData->currentWorkspace->next;
    (*cursor)++;
  }
}

void renameWorkspace(char name[NAME_LENGTH]) {
  char newName[NAME_LENGTH] = "";

  if (promptString("New Title", newName, NAME_LENGTH)) {
    cpyStr(name, newName, TITLE_LENGTH);
  }
}

