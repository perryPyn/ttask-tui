#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include <ncurses.h>

void cpyStr(char *dest, const char *src);
void drawRoundedBox(WINDOW *win, const char title[]);
void checkDimmedParents(WINDOW *win, Node *node);

#endif // !UTILS_H
