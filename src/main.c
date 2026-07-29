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

  app->head = createNode(&(Task){/*0 ,*/ 0, "Head"});
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
    moveUp(app);
    break;
  case 'j':
    moveDown(app);
    break;
  case ' ':
    toggleTaskStatus(app->currentNode, app->cursorLine);
    writeFile(app->head, app->taskLength);
    break;
  case 'a':
    appendTask(app);
    writeFile(app->head, app->taskLength);
    break;
  case 'c':
    app->currentNode->task.status = (app->currentNode->task.status + 1) % 4;
    break;
  case 'x': {
    removeTask(app);
    writeFile(app->head, app->taskLength);
    break;
  }
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
