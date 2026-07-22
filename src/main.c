#include "main.h"
#include "file.h"
#include <ncurses.h>

void setup() {
  // initscr();
  // refresh();

  int taskLength = loadFile();
  printTaskTable(taskLength);
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
  setup();

  while (1) {
    loop();
  }

  return 0;
}
