#include "main.h"
#include "file.h"
#include "log.h"
#include "task.h"
#include "ui.h"
#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>

// void setup(AppState *app) {
//   initUI();
//
//   app->taskLength = loadFile(app->taskTable);
//   app->isRunning = true;
//   app->cursorLine = 0;
//
//   printTaskTable(app->taskTable, app->taskLength);
//
//   refresh();
// }
//
// int loop(AppState *app) {
//   clear();
//   displayTaskTable(app->taskTable, app->taskLength, app->cursorLine);
//   refresh();
//
//   int ch = getch();
//
//   switch (ch) {
//     case 'q':
//       app->isRunning = false;
//       return 0;
//
//     case 'j':
//       app->cursorLine += 1;
//       break;
//     case 'k':
//       app->cursorLine -= 1;
//       break;
//     case ' ':
//       toggleTaskStatus(app->taskTable, app->cursorLine);
//       break;
//     case 'a':
//       addTask(app->taskTable, app->taskLength, &app->taskLength);
//       break;
//     }
//
//     return 1;
// }
//
// void cleanup(AppState *app) {
//   msgLog("[INFO] Saving file and stopping process...\n");
//   writeFile(app->taskTable, app->taskLength);
//   endwin();
// }
//
// int main() {
//   AppState app = {0};
//
//   setup(&app);
//
//   while (app.isRunning && loop(&app)) {
//   }
//
//   cleanup(&app);
//
//   return 0;
// }

struct Node {
  task task;
  struct Node *next;
};

int main() {

  struct Node n1;
  struct Node n2;
  struct Node n3;

  struct Node *head = &n1;
  struct Node *second = &n2;
  struct Node *third = &n3;

  // Assign data and link nodes
  head->task = (task){0, "n1"};
  head->next = second;

  second->task = (task){0, "n2"};
  second->next = third;

  third->task = (task){0, "n3"};
  third->next = NULL;

  // Print linked list
  struct Node *temp = head;
  while (temp != NULL) {
    printf("%s -> ", temp->task.title);
    temp = temp->next;
  }
  printf("NULL\n");

  return 0;
}
