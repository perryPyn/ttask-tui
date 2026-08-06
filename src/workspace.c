#include "workspace.h"
#include "log.h"
#include "node.h"
#include "types.h"
#include "utils.h"
#include "workspaceNode.h"
#include <ncurses.h>
#include <stdio.h>

void appendWorkspace(WorkspaceData *workspaceData, int *cursor) {
  // Creating new window for typing
  int height, width;
  getmaxyx(stdscr, height, width);
  int starty = (1 - 0.3) * height / 2, startx = (1 - 0.7) * width / 2;
  height *= 0.3;
  width *= 0.7;
  WINDOW *win = newwin(height, width, starty, startx);
  WINDOW *content = derwin(win, height - 2, width - 2, 1, 1);
  drawRoundedBox(win, "New Workspace");
  wnoutrefresh(win);
  wnoutrefresh(content);
  doupdate();

  echo();      // Restoring vision of the user input
  curs_set(1); // Show cursor

  char name[NAME_LENGTH];
  // Get user input
  flushinp();
  wgetnstr(content, name, TITLE_LENGTH - 1);

  noecho();
  curs_set(0);

  delwin(content);
  delwin(win);

  // Creating the workspace
  Node *newHead = createNode(&(Task){0, 0, 0, "Head"});

  TaskData taskData = {newHead, newHead->next, 0};
  addWorkspaceNode(name, &taskData, workspaceData->currentWorkspace);

  workspaceData->length += 1;
  (*cursor)++;
  workspaceData->currentWorkspace = workspaceData->currentWorkspace->next;
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
