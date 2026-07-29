#ifndef MAIN_H
#define MAIN_H

#include "app.h"
#define _XOPEN_SOURCE_EXTENDED 1

void setup(AppState *app);
void loop(AppState *app);
void cleanup(AppState *app);
int main(void);

#endif // !MAIN_H
