/**
 *
 *
 *        ___         ___                                      ,-.
 *      ,--.'|_     ,--.'|_                                ,--/ /|
 *      |  | :,'    |  | :,'                             ,--. :/ |
 *      :  : ' :    :  : ' :                  .--.--.    :  : ' /
 *    .;__,'  /   .;__,'  /      ,--.--.     /  /    '   |  '  /
 *    |  |   |    |  |   |      /       \   |  :  /`./   '  |  :
 *    :__,'| :    :__,'| :     .--.  .-. |  |  :  ;_     |  |   \
 *      '  : |__    '  : |__    \__\/: . .   \  \    `.  '  : |. \
 *      |  | '.'|   |  | '.'|   ," .--.; |    `----.   \ |  | ' \ \
 *      ;  :    ;   ;  :    ;  /  /  ,.  |   /  /`--'  / '  : |--'
 *      |  ,   /    |  ,   /  ;  :   .'   \ '--'.     /  ;  |,'
 *       ---`-'      ---`-'   |  ,     .-./   `--'---'   '--'
 *                             `--`---'
 *
 */

#include "config.h"
#include "file.h"
#include "input.h"
#include "log.h"
#include "node.h"
#include "types.h"
#include "ui.h"
#include "workspaceNode.h"
#include <ncurses.h>
#include <signal.h>

static volatile sig_atomic_t keepRunning = 1;

static void handleSignal(int sig) {
  (void)sig;
  keepRunning = 0;
}

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

  // Allow sleep if no new entries
  nodelay(activePanel->content, FALSE);
  int ch = wgetch(activePanel->content);

  // If terminal closed
  if (ch == ERR && (feof(stdin) || ferror(stdin))) {
    app->isRunning = false; // <-- CRITIQUE : stoppe la boucle du main
    return;
  }

  handleInput(app, config->filePath, activePanel->content, ch);
}

static void cleanup(char *filePath, WorkspaceNode *headWorkspace) {
  msgLog("[INFO] Saving file at %s\n", filePath);
  writeFile(headWorkspace, filePath);
  msgLog("[INFO] Stopping process...\n");
  endwin();
}

int main(void) {
  msgLog(
      "\n\n\n\n                                                              \n"
      "                                                              \n"
      "    ___         ___                                      ,-.  \n"
      "  ,--.'|_     ,--.'|_                                ,--/ /|  \n"
      "  |  | :,'    |  | :,'                             ,--. :/ |  \n"
      "  :  : ' :    :  : ' :                  .--.--.    :  : ' /   \n"
      ".;__,'  /   .;__,'  /      ,--.--.     /  /    '   |  '  /    \n"
      "|  |   |    |  |   |      /       \\   |  :  /`./   '  |  :    \n"
      ":__,'| :    :__,'| :     .--.  .-. |  |  :  ;_     |  |   \\   \n"
      "  '  : |__    '  : |__    \\__\\/: . .   \\  \\    `.  '  : |. \\  \n"
      "  |  | '.'|   |  | '.'|   ,\" .--.; |    `----.   \\ |  | ' \\ \\ \n"
      "  ;  :    ;   ;  :    ;  /  /  ,.  |   /  /`--'  / '  : |--'  \n"
      "  |  ,   /    |  ,   /  ;  :   .'   \\ '--'.     /  ;  |,'     \n"
      "   ---`-'      ---`-'   |  ,     .-./   `--'---'   '--'       \n"
      "                         `--`---'                             \n"
      "                                                              \n");
  msgLog("\n[INFO] Starting new process...\n");

  signal(SIGHUP, handleSignal);
  signal(SIGINT, handleSignal);
  signal(SIGTERM, handleSignal);

  initUI();

  AppConfig config = initConfig();
  AppState app = {0};
  setup(&app, &config);

  while (app.isRunning && keepRunning) {
    loop(&app, &config);
  }

  cleanup(config.filePath, app.workspaceData.headWorkspace);

  return 0;
}
