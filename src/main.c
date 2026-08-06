#include "config.h"
#include "file.h"
#include "input.h"
#include "log.h"
#include "node.h"
#include "types.h"
#include "ui.h"
#include "workspaceNode.h"
#include <ncurses.h>

static void setup(AppState *app, AppConfig *config) {
  app->isRunning = true;
  app->activeFocus = FOCUS_TASKS;

  TaskData taskData = {.head = createNode(&(Task){0, 0, 0, "Head"}),
                       .currentNode = NULL,
                       .length = 0};

  app->workspaceData.headWorkspace = createWorkspace("Default", &taskData);
  app->workspaceData.currentWorkspace = app->workspaceData.headWorkspace;
  app->workspaceData.length = 1;

  loadFile(&app->workspaceData, config->filePath);

  initWin(app);
  app->tasksPanel.cursor = 0;
}

static void loop(AppState *app, AppConfig *config) {
  Panel *activePanel =
      (app->activeFocus == FOCUS_TASKS) ? &app->tasksPanel : &app->sidebarPanel;

  renderUI(app, activePanel->win);

  int ch = wgetch(activePanel->content);
  handleInput(app, config->filePath, activePanel->content, ch);
}

static void cleanup(char *filePath, WorkspaceNode *headWorkspace) {
  msgLog("[INFO] Saving file at %s\n", filePath);
  writeFile(headWorkspace, filePath);
  msgLog("[INFO] Stopping process...\n");
  endwin();
}

int main() {
  msgLog("\n\n\n\n\n[INFO] Starting new process...\n");
  initUI();

  AppConfig config = initConfig();

  AppState app = {0};
  setup(&app, &config);

  while (app.isRunning) {
    loop(&app, &config);
  }

  cleanup(config.filePath, app.workspaceData.headWorkspace);

  return 0;
}
