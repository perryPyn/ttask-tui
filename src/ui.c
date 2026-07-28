#include "ui.h"
#include "log.h"
#include "node.h"
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>

void initUI(void) {
  setlocale(LC_ALL, ""); // For use of UTF-8 characters
  initscr();
  cbreak();
  noecho();             // Hide user input
  keypad(stdscr, TRUE); // Enable keypad
  curs_set(0);          // Hide cursor
}

void strikoutLine(char *title[TITLE_LENGTH]) { return; }

void displayNodeTable(Node *head, int taskLength, int cursorLine) {
  // msgLog("[INFO] Diplaying lines :\n");
  Node *node = head->next;
  for (int i = 0; node != NULL; i++, node = node->next) {
    // msgLog("[INFO] Line %d\n", i);

    if (i == cursorLine) {
      attron(A_STANDOUT);
    }

    char *bulletPoints = "□";
    if (node->task.isDone == 1) {
      attron(A_DIM | A_ITALIC);
      bulletPoints = "▣";
    }

    printw("%s %s\n", bulletPoints, node->task.title);
    attroff(A_STANDOUT | A_DIM | A_ITALIC);
  }
}
