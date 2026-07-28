#ifndef NODE_H
#define NODE_H

#include "task.h"

typedef struct Node {
  Task task;
  struct Node *next;
  struct Node *previous;
} Node;

Node *createNode(Task *task);
void addNode(Node *previous, Node *node, Node *next);
void removeNode(Node *node);
void addNodeAtIndex(Task *task, Node *head, int index);
void removeNodeAtIndex(Node *head, int index);
void printNodes(Node *head);
void toggleTaskStatus(Node *node, int lineNumber);

#endif // !NODE_H
