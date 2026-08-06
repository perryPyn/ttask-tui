#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include <ncurses.h>

void cpyStr(char *dest, const char *src, int charLength);
bool promptString(const char *boxTitle, char *outStr, size_t maxLen);
void drawRoundedBox(WINDOW *win, const char title[]);
bool checkForDimmedParents(Node *node);

#endif // !UTILS_H
