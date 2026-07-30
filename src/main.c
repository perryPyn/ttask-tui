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

  TaskData taskData = {createNode(&(Task){0, 0, "Head"})};
  taskData.length = loadFile(taskData.head) - 1;
  taskData.currentNode = taskData.head->next;
  app->workspaceData.headWorkspace = createWorkspace("Default", &taskData);
  app->workspaceData.currentWorkspace = app->workspaceData.headWorkspace;

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

static void cleanup(TaskData *taskData) {
  msgLog("[INFO] Saving file and stopping process...\n");
  writeFile(taskData->head);
  endwin();
}

int main() {
  AppState app = {0};

  setup(&app);

  while (app.isRunning) {
    loop(&app);
  }

  cleanup(&app.workspaceData.currentWorkspace->taskData);

  return 0;
}
