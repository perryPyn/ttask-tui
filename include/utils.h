#ifndef UTILS_H
#define UTILS_H

#include "app.h"

void cpyStr(char *dest, const char *src);
void appendTask(AppState *app);
void removeTask(AppState *app);
void moveDown(AppState *app);
void moveUp(AppState *app);
void checkDimmedParents(Node *node);

#endif // !UTILS_H
