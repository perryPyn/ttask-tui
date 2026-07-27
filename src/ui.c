#include "ui.h"
#include "log.h"
#include "task.h"
#include <locale.h>
#include <ncurses.h>

void initUI(void) {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
}

void strikoutLine(char *title[TITLE_LENGTH]) { return; }

void displayTaskTable(Task taskTable[TABLE_LENGTH], int taskLength,
                      int cursorLine) {
  for (int i = 0; i < taskLength; i++) {
    if (i == cursorLine) {
      attron(A_STANDOUT);
    }

    char *bulletPoints = "□";
    if (taskTable[i].isDone == 1) {
      attron(A_DIM | A_ITALIC);
      bulletPoints = "▣";
    }

    printw("%s %s\n", bulletPoints, taskTable[i].title);
    attroff(A_STANDOUT | A_DIM | A_ITALIC);
  }
}
