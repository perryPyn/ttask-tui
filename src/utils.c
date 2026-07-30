#include "utils.h"
#include <stddef.h>
#include <string.h>

void cpyStr(char *dest, const char *src) {
  size_t len = strlen(src);
  if (len >= TITLE_LENGTH) {
    len = TITLE_LENGTH - 1;
  }
  memcpy(dest, src, len);
  dest[len] = '\0';
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

void checkDimmedParents(WINDOW *win, Node *node) {
  if (node == NULL)
    return;

  int targetIndentation = node->task.indentation;
  Node *parentNode = node->previous;

  while (parentNode != NULL && parentNode->previous != NULL) {
    if (parentNode->task.indentation < targetIndentation) {
      if (parentNode->task.status == TASK_DONE ||
          parentNode->task.status == TASK_ON_HOLD) {
        wattron(win, A_DIM);
        return;
      }
      targetIndentation = parentNode->task.indentation;

      if (targetIndentation == 0) {
        break;
      }
    }
    parentNode = parentNode->previous;
  }
}
