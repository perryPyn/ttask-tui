#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include <ncurses.h>

void cpyStr(char *dest, const char *src, int charLength);
void drawRoundedBox(WINDOW *win, const char title[]);
bool checkForDimmedParents(Node *node);

#endif // !UTILS_H
