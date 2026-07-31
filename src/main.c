#include "file.h"
#include "input.h"
#include "log.h"
#include "node.h"
#include "types.h"
#include "ui.h"
#include "workspaceNode.h"
#include <ncurses.h>

static void setup(AppState *app) {
  initUI();

  app->isRunning = true;
  app->activeFocus = FOCUS_TASKS;

  TaskData taskData = {.head = createNode(&(Task){0, 0, "Head"}),
                       .currentNode = NULL,
                       .length = 0};

  app->workspaceData.headWorkspace = createWorkspace("Default", &taskData);
  app->workspaceData.currentWorkspace = app->workspaceData.headWorkspace;
  app->workspaceData.length = 1;

  loadFile(&app->workspaceData);

  initWin(app);
  app->tasksPanel.cursor = 0;
}

static void loop(AppState *app) {
  renderUI(app);

  WINDOW *activeWin = (app->activeFocus == FOCUS_TASKS)
                          ? app->tasksPanel.content
                          : app->sidebarPanel.content;

  int ch = wgetch(activeWin);
  handleInput(app, activeWin, ch);
}

static void cleanup(WorkspaceNode *headWorkspace) {
  msgLog("[INFO] Saving file and stopping process...\n");
  writeFile(headWorkspace);
  endwin();
}

int main() {
  AppState app = {0};

  setup(&app);

  while (app.isRunning) {
    loop(&app);
  }

  cleanup(app.workspaceData.headWorkspace);

  return 0;
}
