#ifndef UI_H
#define UI_H

#include "types.h"
#include <ncurses.h>

void initUI(void);
void initWin(AppState *app);
void destWin(AppState *app);
void renderUI(AppState *app, WINDOW *activeWindow);

#endif // !UI_H
