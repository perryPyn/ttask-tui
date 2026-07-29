#include "ui.h"
#include "log.h"
#include "node.h"
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
void displayNodeTable(Node *head, int taskLength, int cursorLine) {
  // msgLog("[INFO] Diplaying lines :\n");
  Node *node = head->next;
  for (int i = 0; node != NULL; i++, node = node->next) {
    // msgLog("[INFO] Line %d\n", i);

    if (i == cursorLine) {
      attron(A_STANDOUT);
    }

    char title[strlen(node->task.title) * 3 + 1];
    switch (node->task.status) {
    case 0: // TASK_TODO
      cpyStr(title, node->task.title);
      break;
    case 1: // TASK_IN_PROGRESS
      attron(A_BOLD);
      cpyStr(title, node->task.title);
      break;
    case 2: // TASK_DONE
      attron(A_DIM);
      strikeThrough(node->task.title, title);
      break;
    case 3: // TASK_ON_HOLD
      attron(A_DIM);
      cpyStr(title, node->task.title);
      break;
    }

    printw("%s %s\n", STATUS_SYMBOLS[node->task.status], title);
    attroff(A_STANDOUT | A_DIM | A_BOLD);
  }
}
