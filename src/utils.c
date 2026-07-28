#include "utils.h"
#include "app.h"
#include "log.h"
#include "task.h"
#include <ncurses.h>
#include <stddef.h>
#include <string.h>

void cpyStr(char *dest, const char *src) {
  size_t len = strlen(src);
  if (len >= TITLE_LENGTH) {
    len = TITLE_LENGTH - 1;
  }
  memcpy(dest, src, len);
  dest[len] = '\0';
}

void appendTask(AppState *app) {
  echo(); // Restoring vision on the user input

  char title[TITLE_LENGTH];
  // Get user input
  getstr(title);

  // Creating the node
  Task task = {0, ""};
  cpyStr(task.title, title);
  addNode(&task, app->currentNode);

  app->taskLength += 1;
  app->cursorLine += 1;
  app->currentNode = app->currentNode->next;

  noecho();
}

void removeTask(AppState *app) {
  if (app->currentNode == NULL) {
    msgLog("[WARN] current node is NULL");
    return;
  }
  Node *toDelete = app->currentNode;

  if (app->currentNode->next == NULL) {
    app->currentNode = app->currentNode->previous;
    app->cursorLine -= 1;
  } else {
    app->currentNode = app->currentNode->next;
  }

  removeNode(toDelete);
  app->taskLength -= 1;
}

void moveUp(AppState *app) {
  app->cursorLine = (app->cursorLine - 1 < 0) ? 0 : app->cursorLine - 1;
  app->currentNode = (app->currentNode->previous->previous != NULL)
                         ? app->currentNode->previous
                         : app->currentNode;
}

void moveDown(AppState *app) {
  app->cursorLine = (app->cursorLine + 1 > app->taskLength)
                        ? app->taskLength
                        : app->cursorLine + 1;
  app->currentNode = (app->currentNode->next != NULL) ? app->currentNode->next
                                                      : app->currentNode;
}
