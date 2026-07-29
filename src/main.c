#include "main.h"
#include "file.h"
#include "log.h"
#include "node.h"
#include "task.h"
#include "ui.h"
#include "utils.h"
#include <ncurses.h>

void setup(AppState *app) {
  initUI();
  initWin(app);

  app->head = createNode(&(Task){0, 0, "Head"});
  app->taskLength = loadFile(app->head) - 1;
  app->currentNode = app->head->next;
  app->isRunning = true;
  app->cursorLine = 0;

  printNodes(app->head);
}

void loop(AppState *app) {
  werase(app->sidebarWin);
  werase(app->sidebarContent);
  werase(app->tasksWin);
  werase(app->tasksContent);

  if (app->activeWin == app->tasksContent) {
    displayNodeTable(app->tasksContent, app->head, app->taskLength,
                     app->cursorLine);
  }

  box(app->sidebarWin, 0, 0);
  box(app->tasksWin, 0, 0);
  wnoutrefresh(app->sidebarWin);
  wnoutrefresh(app->sidebarContent);
  wnoutrefresh(app->tasksWin);
  wnoutrefresh(app->tasksContent);

  doupdate();

  int ch = wgetch(app->activeWin);

  switch (ch) {
  case KEY_RESIZE:
    resizeterm(0, 0);
    clear();
    destWin(app);
    initWin(app);
    break;
  case '\t':
    if (app->activeWin == app->tasksContent) {
      app->activeWin = app->sidebarContent;
    } else {
      app->activeWin = app->tasksContent;
    }
    break;
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
    app->currentNode->task.indentation =
        app->currentNode->previous->task.indentation;
    writeFile(app->head, app->taskLength);
    break;
  case 'A':
    appendTask(app);
    app->currentNode->task.indentation =
        app->currentNode->previous->task.indentation + 2;
    writeFile(app->head, app->taskLength);
    break;
  case '>':
    app->currentNode->task.indentation = app->currentNode->task.indentation + 2;
    writeFile(app->head, app->taskLength);
    break;
  case '<':
    if (app->currentNode->task.indentation > 0) {
      app->currentNode->task.indentation =
          app->currentNode->task.indentation - 2;
      writeFile(app->head, app->taskLength);
    }
    break;
  case 'c':
    app->currentNode->task.status = (app->currentNode->task.status + 1) % 4;
    writeFile(app->head, app->taskLength);
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
