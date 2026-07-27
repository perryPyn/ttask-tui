#include "main.h"
#include "file.h"
#include "log.h"
#include "task.h"
#include "ui.h"
#define _XOPEN_SOURCE_EXTENDED 1
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

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

typedef struct Node {
  Task task;
  struct Node *next;
  struct Node *previous;
} Node;

Node *createNode(Task task) {
  Node *node = NULL;
  node = (Node *)malloc(sizeof(Node));

  if (!node) {
    msgLog("[CRIT] Memory allocation failed\n");
    return NULL;
  }

  node->task = task;
  node->previous = NULL;
  node->next = NULL;

  return node;
}

void addNode(Node *previous, Node *node, Node *next) {
  if (node == NULL) {
    return;
  }

  node->previous = previous;
  node->next = next;

  // If placed at the top
  if (next != NULL) {
    next->previous = node;
  }
  // If placed at the bottom
  if (previous != NULL) {
    previous->next = node;
  }
}

void removeNode(Node *node) {
  if (node == NULL) {
    return;
  }

  // If placed at the top
  if (node->next != NULL) {
    node->next->previous = node->previous;
  }
  // If placed at the bottom
  if (node->previous != NULL) {
    node->previous->next = node->next;
  }
  free(node);
}

void addNodeAtIndex(Task task, Node *head, int index) {
  // Creation of the new node
  Node *node = createNode(task);

  // Looking for the spot for the new node
  Node *nodeAtIndex = head;
  for (int i = 0; i < index; i++) {
    if (nodeAtIndex->next == NULL) {
      break;
    }
    nodeAtIndex = nodeAtIndex->next;
  }

  // Insert new node
  addNode(nodeAtIndex, node, nodeAtIndex->next);
}

void removeNodeAtIndex(Node *head, int index) {

  Node *nodeAtIndex = head;
  for (int i = 0; i < index; i++) {
    if (nodeAtIndex->next == NULL) {
      break;
    }
    nodeAtIndex = nodeAtIndex->next;
  }

  removeNode(nodeAtIndex);
}

void printNodes(Node *head) {
  Node *temp = head;
  msgLog("[INFO] Printing Node table :\n   ");
  while (temp != NULL) {
    msgLog("%s -> ", temp->task.title);
    temp = temp->next;
  }
  msgLog("NULL\n");
}

int main() {

  Node *head = createNode((Task){0, "Head"});
  printNodes(head);

  addNodeAtIndex((Task){0, "n2"}, head, 2);
  addNodeAtIndex((Task){0, "n4"}, head, 4);
  addNodeAtIndex((Task){0, "n5"}, head, 5);
  printNodes(head);

  addNodeAtIndex((Task){0, "n1"}, head, 0);
  addNodeAtIndex((Task){0, "n3"}, head, 2);
  printNodes(head);

  removeNodeAtIndex(head, 2);
  printNodes(head);

  return 0;
}
