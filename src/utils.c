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
