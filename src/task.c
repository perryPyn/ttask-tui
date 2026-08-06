#include "task.h"
#include "log.h"
#include "node.h"
#include "types.h"
#include "utils.h"
#include <ncurses.h>
#include <string.h>

void appendTask(TaskData *taskData, int *cursor) {
  if (taskData == NULL || taskData->head == NULL) {
    return;
  }

  bool wasEmpty = (taskData->currentNode == NULL);
  if (wasEmpty) {
    taskData->currentNode = taskData->head;
  }

  // Creating
  int height, width;
  getmaxyx(stdscr, height, width);
  int starty = (1 - 0.3) * height / 2, startx = (1 - 0.7) * width / 2;
  height *= 0.3;
  width *= 0.7;

  WINDOW *win = newwin(height, width, starty, startx);
  WINDOW *content = derwin(win, height - 2, width - 2, 1, 1);
  drawRoundedBox(win, "New Task");
  wnoutrefresh(win);
  wnoutrefresh(content);
  doupdate();

  echo();
  curs_set(1);
  nodelay(content, FALSE);

  char title[TITLE_LENGTH] = "";
  flushinp();
  int res = wgetnstr(content, title, TITLE_LENGTH - 1);

  noecho();
  curs_set(0);
  delwin(content);
  delwin(win);

  if (res == ERR || strlen(title) == 0) {
    if (wasEmpty) {
      taskData->currentNode = NULL;
    }
    return;
  }

  // Creating new node
  Task task = {0, 0, 0, ""};
  cpyStr(task.title, title, TITLE_LENGTH);
  addNode(&task, taskData->currentNode);

  taskData->length += 1;
  taskData->currentNode = taskData->currentNode->next;

  if (wasEmpty) {
    *cursor = 0;
  } else {
    (*cursor)++;
  }
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
  if (taskData->currentNode->previous != NULL &&
      taskData->currentNode->previous->previous != NULL) {
    taskData->currentNode = taskData->currentNode->previous;
    (*cursor)--;
  }
}

void moveDown(TaskData *taskData, int *cursor) {
  if (taskData->currentNode == NULL) {
    return;
  }
  if (taskData->currentNode->next != NULL) {
    taskData->currentNode = taskData->currentNode->next;
    (*cursor)++;
  }
}

void increaseImportance(TaskData *taskData) {
  if (taskData->currentNode == NULL) {
    return;
  }
  if (taskData->currentNode->task.importance < 3) {
    (taskData->currentNode->task.importance)++;
  }
}

void decreaseImportance(TaskData *taskData) {
  if (taskData->currentNode == NULL) {
    return;
  }
  if (taskData->currentNode->task.importance > 0) {
    (taskData->currentNode->task.importance)--;
  }
}

void renameTask(char title[TITLE_LENGTH]) {

  // Creating typing window
  int height, width;
  getmaxyx(stdscr, height, width);
  int starty = (1 - 0.3) * height / 2, startx = (1 - 0.7) * width / 2;
  height *= 0.3;
  width *= 0.7;

  WINDOW *win = newwin(height, width, starty, startx);
  WINDOW *content = derwin(win, height - 2, width - 2, 1, 1);
  drawRoundedBox(win, "New Title");
  wnoutrefresh(win);
  wnoutrefresh(content);
  doupdate();

  echo();
  curs_set(1);
  nodelay(content, FALSE);

  char newTitle[TITLE_LENGTH] = "";
  flushinp();
  int res = wgetnstr(content, newTitle, TITLE_LENGTH - 1);

  noecho();
  curs_set(0);
  delwin(content);
  delwin(win);

  if (res == ERR) {
    return;
  }

  // Changing the title
  cpyStr(title, newTitle, TITLE_LENGTH);
}
