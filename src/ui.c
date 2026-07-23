#include "ui.h"
#include "log.h"
#include <ncurses.h>

void initUI(void) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
}

void displayTaskTable(task taskTable[TABLE_LENGTH], int taskLength, int cursorLine) {
  for (int i = 0; i < taskLength; i++) {
    if(i==cursorLine) {
      attron(A_REVERSE);
    }
    printw("- [%c] %s\n", taskTable[i].isDone ? 'x' : ' ', taskTable[i].title);
    attroff(A_REVERSE);
  }
}
