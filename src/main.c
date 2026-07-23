#include "main.h"
#include "file.h"
#include "log.h"
#include "task.h"
#include "ui.h"
#include <ncurses.h>

void setup(AppState *app) {
  initUI();

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

  if (ch == 'q') {
    app->isRunning = false;
    return 0;
  }

  if (ch == 'j') {
    app->cursorLine += 1;
  }
  if (ch == 'k') {
    app->cursorLine -= 1;
  }

  if (ch == ' ' || ch == '\n') {
    toggleTaskStatus(app->taskTable, app->cursorLine);
  }

  return 1;
}

void testColor() {
  start_color();

  // init_pair(1, COLOR_BLACK, COLOR_RED); // Paire 1 : Texte rouge sur fond
  // noir attron(COLOR_PAIR(1)); printw("Texte en rouge");
  // attroff(COLOR_PAIR(1));
}

void cleanup(AppState *app) {
  msgLog("[INFO] Saving file and stopping process...\n");
  writeFile(app->taskTable, app->taskLength);
  endwin();
}

int main() {
  AppState app = {0};

  setup(&app);

  while (app.isRunning && loop(&app)) {
  }

  cleanup(&app);

  return 0;
}
