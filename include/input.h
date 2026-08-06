#ifndef INPUT_H
#define INPUT_H

#include "types.h"
#include <ncurses.h>

void handleInput(AppState *app, char *filePath, WINDOW *activeWin, int ch);

#endif // !INPUT_H
