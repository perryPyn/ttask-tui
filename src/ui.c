#include "ui.h"
#include "types.h"
#include "utils.h"
#include <locale.h>
#include <ncurses.h>
#include <string.h>

static const char *STATUS_SYMBOLS[TASK_COUNT] = {[TASK_TODO] = "○",
                                                 [TASK_IN_PROGRESS] = "◐",
                                                 [TASK_DONE] = "●",
                                                 [TASK_ON_HOLD] = "◌"};

/*---Manage appearence, maybe subject to move---*/
static void strikeThrough(const char *src, char *dest) {
  int j = 0;
  for (int i = 0; src[i] != '\0'; i++) {
    dest[j++] = src[i];
    dest[j++] = '\xCC';
    dest[j++] = '\xB6';
  }
  dest[j] = '\0';
}

// ◐ | ◌ | ● | ○
static void displayNodeTable(WINDOW *win, Node *head, int cursor) {
  // msgLog("[INFO] Diplaying lines :\n");
  Node *node = head->next;
  for (int i = 0; node != NULL; i++, node = node->next) {
    // msgLog("[INFO] Line %d\n", i);

    if (i == cursor) {
      wattron(win, A_STANDOUT);
    }

    char title[strlen(node->task.title) * 3 + 1];
    switch (node->task.status) {
    case 0: // TASK_TODO
      cpyStr(title, node->task.title, TITLE_LENGTH);
      break;
    case 1: // TASK_IN_PROGRESS
      wattron(win, A_BOLD);
      cpyStr(title, node->task.title, TITLE_LENGTH);
      break;
    case 2: // TASK_DONE
      wattron(win, A_DIM);
      strikeThrough(node->task.title, title);
      break;
    case 3: // TASK_ON_HOLD
      wattron(win, A_DIM);
      cpyStr(title, node->task.title, TITLE_LENGTH);
      break;
    }

    // Check if a parent is marked as DONE or ON_HOLD
    checkDimmedParents(win, node);

    wprintw(win, "%*s%s %s\n", node->task.indentation, "",
            STATUS_SYMBOLS[node->task.status], title);
    wattroff(win, A_STANDOUT | A_DIM | A_BOLD);
  }
}

static void displaySidebar(WINDOW *win, WorkspaceNode *headWorkspace,
                           int cursor) {
  WorkspaceNode *workspaceNode = headWorkspace;
  for (int i = 0; workspaceNode != NULL;
       i++, workspaceNode = workspaceNode->next) {

    if (i == cursor) {
      wattron(win, A_STANDOUT);
    }

    wprintw(win, "%s\n", workspaceNode->name);
    wattroff(win, A_STANDOUT);
  }
}

void initUI(void) {
  setlocale(LC_ALL, ""); // For use of UTF-8 characters
  initscr();
  cbreak();
  noecho();             // Hide user input
  keypad(stdscr, TRUE); // Enable keypad
  curs_set(0);          // Hide cursor
}

/*---Manage windows and panels---*/
static void initPanel(Panel *panel, int height, int width, int starty,
                      int startx) {
  panel->win = newwin(height, width, starty, startx);
  panel->content = derwin(panel->win, height - 2, width - 2, 1, 1);
}

void initWin(AppState *app) {
  int height, width;
  getmaxyx(stdscr, height, width);

  // Setting up window ratio
  int sidebarWidth = width * 0.3;
  int tasksWidth = width - sidebarWidth;

  // Creating container and content windows
  initPanel(&app->sidebarPanel, height, sidebarWidth, 0, 0);
  initPanel(&app->tasksPanel, height, tasksWidth, 0, sidebarWidth);
}

static void destPanel(Panel *panel) {
  if (panel->content) {
    delwin(panel->content);
    panel->content = NULL;
  }
  if (panel->win) {
    delwin(panel->win);
    panel->win = NULL;
  }
}

void destWin(AppState *app) {
  destPanel(&app->sidebarPanel);
  destPanel(&app->tasksPanel);
}

/*---Manage render elements---*/
static void renderSidebar(Panel *panel, WorkspaceData *workspaceData) {
  werase(panel->win);
  werase(panel->content);

  displaySidebar(panel->content, workspaceData->headWorkspace, panel->cursor);
  drawRoundedBox(panel->win, "Workspaces");

  wnoutrefresh(panel->win);
  wnoutrefresh(panel->content);
}

static void renderTasks(Panel *panel, TaskData *taskData) {
  werase(panel->win);
  werase(panel->content);

  displayNodeTable(panel->content, taskData->head, panel->cursor);

  drawRoundedBox(panel->win, "Tasks");

  wnoutrefresh(panel->win);
  wnoutrefresh(panel->content);
}

void renderUI(AppState *app) {
  renderSidebar(&app->sidebarPanel, &app->workspaceData);
  renderTasks(&app->tasksPanel, &app->workspaceData.currentWorkspace->taskData);

  doupdate();
}
