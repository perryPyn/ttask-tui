#ifndef NODE_H
#define NODE_H

#include "types.h"

Node *createNode(Task *task);
void addNode(Task *task, Node *nodeToTarget);
Node *appendNode(Task *task, Node *previousNode);
void removeNode(Node *node);
void addNodeAtIndex(Task *task, Node *head, int index);
void removeNodeAtIndex(Node *head, int index);
void printNodes(Node *head);
void toggleNode(Node *node);

#endif // !NODE_H
