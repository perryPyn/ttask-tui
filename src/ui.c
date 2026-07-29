#include "ui.h"
#include "app.h"
#include "task.h"
#include "utils.h"
#include <locale.h>
#include <ncurses.h>
#include <string.h>

static const char *STATUS_SYMBOLS[TASK_COUNT] = {[TASK_TODO] = "○",
                                                 [TASK_IN_PROGRESS] = "◐",
                                                 [TASK_DONE] = "●",
                                                 [TASK_ON_HOLD] = "◌"};

void initUI(void) {
  setlocale(LC_ALL, ""); // For use of UTF-8 characters
  initscr();
  cbreak();
  noecho();             // Hide user input
  keypad(stdscr, TRUE); // Enable keypad
  curs_set(0);          // Hide cursor
}

void initWin(AppState *app) {
  int height, width;
  getmaxyx(stdscr, height, width);

  // Setting up window ratio
  int sidebarWidth = width * 0.3;
  int tasksWidth = width - sidebarWidth;

  // Creating container and content windows
  app->sidebarWin = newwin(height, sidebarWidth, 0, 0);
  app->sidebarContent = derwin(app->sidebarWin, height - 2, sidebarWidth - 2, 1, 1);
  app->tasksWin = newwin(height, tasksWidth, 0, sidebarWidth);
  app->tasksContent = derwin(app->tasksWin, height - 2, sidebarWidth - 2, 1, 1);
  app->activeWin = app->tasksContent;// app->activeWin = app->sidebarContent;
}

void destWin(AppState *app) {
  // Deleting windows
  delwin(app->tasksContent);
  delwin(app->sidebarContent);
  delwin(app->tasksWin);
  delwin(app->sidebarWin);

  // Freeing pointers
  app->tasksContent = NULL;
  app->sidebarContent = NULL;
  app->tasksWin = NULL;
  app->sidebarWin = NULL;
}

void strikeThrough(const char *src, char *dest) {
  int j = 0;
  for (int i = 0; src[i] != '\0'; i++) {
    dest[j++] = src[i];
    dest[j++] = '\xCC';
    dest[j++] = '\xB6';
  }
  dest[j] = '\0';
}

// ◐ | ◌ | ● | ○
void displayNodeTable(WINDOW *win, Node *head, int taskLength, int cursorLine) {
  // msgLog("[INFO] Diplaying lines :\n");
  Node *node = head->next;
  for (int i = 0; node != NULL; i++, node = node->next) {
    // msgLog("[INFO] Line %d\n", i);

    if (i == cursorLine) {
      wattron(win, A_STANDOUT);
    }

    char title[strlen(node->task.title) * 3 + 1];
    switch (node->task.status) {
    case 0: // TASK_TODO
      cpyStr(title, node->task.title);
      break;
    case 1: // TASK_IN_PROGRESS
      wattron(win, A_BOLD);
      cpyStr(title, node->task.title);
      break;
    case 2: // TASK_DONE
      wattron(win, A_DIM);
      strikeThrough(node->task.title, title);
      break;
    case 3: // TASK_ON_HOLD
      wattron(win, A_DIM);
      cpyStr(title, node->task.title);
      break;
    }

    // Find the first parent that is marked as DONE or ON_HOLD
    checkDimmedParents(win, node);

    wprintw(win, "%*s%s %s\n", node->task.indentation, "",
            STATUS_SYMBOLS[node->task.status], title);
    wattroff(win, A_STANDOUT | A_DIM | A_BOLD);
  }
}
