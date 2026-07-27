#include "main.h"
#include "file.h"
#include "log.h"
#include "task.h"
#include "ui.h"
#include <stdio.h>
#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>

void setup(AppState *app) {
  initUI();

  app->head = createNode((Task){0, "Head"});
  app->taskLength = loadFile(app->taskTable);
  app->isRunning = true;
  app->cursorLine = 0;

  printTaskTable(app->taskTable, app->taskLength);

  refresh();
}

int loop(AppState *app) {
  clear();
  displayTaskTable(app->taskTable, app->taskLength, app->cursorLine);
  refresh();

  int ch = getch();

  switch (ch) {
  case 'q':
    app->isRunning = false;
    return 0;

  case 'j':
    app->cursorLine += 1;
    break;
  case 'k':
    app->cursorLine -= 1;
    break;
  case ' ':
    toggleTaskStatus(app->taskTable, app->cursorLine);
    break;
  case 'a':
    addTask(app->taskTable, app->taskLength, &app->taskLength);
    break;
  }

  return 1;
}

void cleanup(AppState *app) {
  msgLog("[INFO] Saving file and stopping process...\n");
  writeFile(app->taskTable, app->taskLength);
  endwin();
}

int main() {
  AppState app = {0};

  setup(&app);

  printNodes(app.head);

  addNodeAtIndex((Task){0, "n2"}, app.head, 2);
  addNodeAtIndex((Task){0, "n4"}, app.head, 4);
  addNodeAtIndex((Task){0, "n5"}, app.head, 5);
  printNodes(app.head);

  addNodeAtIndex((Task){0, "n1"}, app.head, 0);
  addNodeAtIndex((Task){0, "n3"}, app.head, 2);
  printNodes(app.head);

  removeNodeAtIndex(app.head, 2);
  printNodes(app.head);

  while (app.isRunning && loop(&app)) {
  }

  cleanup(&app);

  return 0;
}
