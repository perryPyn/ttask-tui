#include "main.h"
#include "file.h"
#include "task.h"
#include <ncurses.h>
#include <stdlib.h>

void setup() {
  // initscr();
  // refresh();
}

void loop() {
  // int ch = getch();
  // if (ch == 'q') {
  //   endwin();
  //   stopFile();
  // }
}

void testColor() {
  start_color();

  // init_pair(1, COLOR_BLACK, COLOR_RED); // Paire 1 : Texte rouge sur fond
  // noir attron(COLOR_PAIR(1)); printw("Texte en rouge");
  // attroff(COLOR_PAIR(1));
}

int main() {
  task taskTable[TABLE_LENGTH] = {0};
  setup();

  int taskLength = loadFile(taskTable);
  printTaskTable(taskTable, taskLength);

  toggleTaskStatus(taskTable, 1);
  toggleTaskStatus(taskTable, 3);

  writeFile(taskTable, taskLength);
  exit(0);

  while (1) {
    loop();
  }

  return 0;
}
