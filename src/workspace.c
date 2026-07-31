#include "workspace.h"
#include "node.h"
#include "types.h"
#include "utils.h"
#include "workspaceNode.h"
#include <ncurses.h>

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
  Node *newHead = createNode(&(Task){0, 0, "Head"});

  TaskData taskData = {newHead, newHead->next, 0};
  addWorkspaceNode(name, &taskData, workspaceData->currentWorkspace);

  workspaceData->length += 1;
  (*cursor)++;
  workspaceData->currentWorkspace = workspaceData->currentWorkspace->next;
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
