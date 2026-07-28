#include "main.h"
#include "file.h"
#include "log.h"
#include "node.h"
#include "task.h"
#include "ui.h"
#include "utils.h"
#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>

void setup(AppState *app) {
  initUI();

  app->head = createNode(&(Task){0, "Head"});
  app->taskLength = loadFile(app->head) - 1;
  app->currentNode = app->head->next;
  app->isRunning = true;
  app->cursorLine = 0;

  printNodes(app->head);

  refresh();
}

void loop(AppState *app) {
  clear();
  displayNodeTable(app->head, app->taskLength, app->cursorLine);
  refresh();

  int ch = getch();

  switch (ch) {
  case 'q':
    app->isRunning = 0;
    break;
  case 'k':
    app->cursorLine = (app->cursorLine - 1 < 0) ? 0 : app->cursorLine - 1;
    app->currentNode = (app->currentNode->previous->previous != NULL)
                           ? app->currentNode->previous
                           : app->currentNode;
    break;
  case 'j':
    app->cursorLine = (app->cursorLine + 1 > app->taskLength)
                          ? app->taskLength
                          : app->cursorLine + 1;
    app->currentNode = (app->currentNode->next != NULL) ? app->currentNode->next
                                                        : app->currentNode;
    break;
  case ' ':
    toggleTaskStatus(app->currentNode, app->cursorLine);
    break;
  case 'a':
    echo(); // Restoring vision on the user input

    char title[TITLE_LENGTH];
    // Get user input
    getstr(title);

    // Creating the node
    Task task = {0, ""};
    cpyStr(task.title, title);
    addNodeAtIndex(&task, app->head, app->cursorLine);

    app->taskLength += 1;

    noecho();
    break;

  case 'x':
    removeNode(app->currentNode);
    app->taskLength -= 1;
    break;
  }
}

void cleanup(AppState *app) {
  msgLog("[INFO] Saving file and stopping process...\n");
  writeFile(app->head, app->taskLength);
  endwin();
}

int main() {
  AppState app = {0};

  setup(&app);

  printNodes(app.head);

  while (app.isRunning) {
    loop(&app);
  }

  cleanup(&app);

  return 0;
}
