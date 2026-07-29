#ifndef UI_H
#define UI_H

#include "app.h"
#include "node.h"
#include <ncurses.h>

void initUI(void);
void initWin(AppState *app);
void destWin(AppState *app);
void displayNodeTable(WINDOW *win, Node *head, int taskLength, int cursorLine);

#endif // !UI_H
