#include "task.h"
#include "log.h"
#include "node.h"
#include "utils.h"
#include <ncurses.h>
#include <stdio.h>

void appendTask(TaskData *taskData, int *cursor) {
  if (taskData->currentNode == NULL) {
    taskData->currentNode = taskData->head;
    (*cursor)--;
  }

  // Creating new window for typing
  int height, width;
  getmaxyx(stdscr, height, width);
  int starty = (1 - 0.3) * height / 2, startx = (1 - 0.7) * width / 2;
  height *= 0.3;
  width *= 0.7;
  WINDOW *win = newwin(height, width, starty, startx);
  WINDOW *content = derwin(win, height - 2, width - 2, 1, 1);
  box(win, 0, 0);
  wnoutrefresh(win);
  wnoutrefresh(content);
  doupdate();

  echo();      // Restoring vision of the user input
  curs_set(1); // Show cursor

  char title[TITLE_LENGTH];
  // Get user input
  flushinp();
  wgetnstr(content, title, TITLE_LENGTH);
  // wgetstr(content, title);

  noecho();
  curs_set(0);

  delwin(content);
  delwin(win);

  // Creating the node
  Task task = {0, 0, ""};
  cpyStr(task.title, title);
  addNode(&task, taskData->currentNode);

  taskData->length += 1;
  (*cursor)++;
  taskData->currentNode = taskData->currentNode->next;
}

void removeTask(TaskData *taskData, int *cursor) {
  if (taskData->currentNode == NULL) {
    msgLog("[WARN] current node is NULL");
    return;
  }
  Node *toDelete = taskData->currentNode;

  if (taskData->currentNode->next == NULL) {
    taskData->currentNode = taskData->currentNode->previous;
    (*cursor)--;
  } else {
    taskData->currentNode = taskData->currentNode->next;
  }

  removeNode(toDelete);
  taskData->length -= 1;
}

void moveUp(TaskData *taskData, int *cursor) {
  if (taskData->currentNode == NULL) {
    return;
  }
  if (*cursor > 0) {
    (*cursor)--;
  }
  if (taskData->currentNode->previous != NULL &&
      taskData->currentNode->previous->previous != NULL) {
    taskData->currentNode = taskData->currentNode->previous;
  }

  // taskData->currentNode = (taskData->currentNode->previous->previous != NULL)
  //                             ? taskData->currentNode->previous
  //                             : taskData->currentNode;
}

void moveDown(TaskData *taskData, int *cursor) {
  if (taskData->currentNode == NULL) {
    return;
  }
  if (*cursor < taskData->length) {
    (*cursor)++;
  }
  taskData->currentNode = (taskData->currentNode->next != NULL)
                              ? taskData->currentNode->next
                              : taskData->currentNode;
}
