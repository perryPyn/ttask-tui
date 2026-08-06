#include "utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

void cpyStr(char *dest, const char *src, int charLength) {
  size_t len = strlen(src);
  if (len >= charLength) {
    len = charLength - 1;
  }
  memcpy(dest, src, len);
  dest[len] = '\0';
}

bool promptString(const char *boxTitle, char *outStr, size_t maxLen) {
  int height, width;
  getmaxyx(stdscr, height, width);
  int starty = (1 - 0.3) * height / 2;
  int startx = (1 - 0.7) * width / 2;
  height *= 0.3;
  width *= 0.7;

  WINDOW *win = newwin(height, width, starty, startx);
  WINDOW *content = derwin(win, height - 2, width - 2, 1, 1);
  drawRoundedBox(win, boxTitle);
  wnoutrefresh(win);
  wnoutrefresh(content);
  doupdate();

  echo();
  curs_set(1);
  nodelay(content, FALSE);

  flushinp();
  int res = wgetnstr(content, outStr, maxLen - 1);

  noecho();
  curs_set(0);
  delwin(content);
  delwin(win);

  return (res != ERR && strlen(outStr) > 0);
}

void drawRoundedBox(WINDOW *win, const char title[]) {
  int height, width;
  getmaxyx(win, height, width);

  if (height < 2 || width < 2)
    return;

  mvwaddstr(win, 0, 0, "╭");
  mvwaddstr(win, 0, width - 1, "╮");
  mvwaddstr(win, height - 1, 0, "╰");
  mvwaddstr(win, height - 1, width - 1, "╯");

  for (int x = 1; x < width - 1; x++) {
    mvwaddstr(win, 0, x, "─");
    mvwaddstr(win, height - 1, x, "─");
  }

  for (int y = 1; y < height - 1; y++) {
    mvwaddstr(win, y, 0, "│");
    mvwaddstr(win, y, width - 1, "│");
  }

  int maxLen = width - 4;
  if (maxLen > 0) {
    mvwprintw(win, 0, 2, " %.*s ", maxLen, title);
  }
}

bool checkForDimmedParents(Node *node) {
  if (node == NULL)
    return false;

  int targetIndentation = node->task.indentation;
  Node *parentNode = node->previous;

  while (parentNode != NULL && parentNode->previous != NULL) {
    if (parentNode->task.indentation < targetIndentation) {
      if (parentNode->task.status == TASK_DONE ||
          parentNode->task.status == TASK_ON_HOLD) {
        return true;
      }
      targetIndentation = parentNode->task.indentation;

      if (targetIndentation == 0) {
        break;
      }
    }
    parentNode = parentNode->previous;
  }
  return false;
}
