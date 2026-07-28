#include "node.h"
#include "log.h"
#include "task.h"
#include <stdlib.h>

Node *createNode(Task *task) {
  Node *node = NULL;
  node = (Node *)malloc(sizeof(Node));

  if (!node) {
    msgLog("[CRIT] Memory allocation failed\n");
    return NULL;
  }

  node->task = *task;
  node->previous = NULL;
  node->next = NULL;

  return node;
}

void addNode(Task *task, Node *nodeToTarget) {
  // Creation of the new node
  Node *node = createNode(task);

  node->previous = nodeToTarget;
  node->next = nodeToTarget->next;

  // If placed at the top
  if (nodeToTarget->next != NULL) {
    nodeToTarget->next->previous = node;
  }
  // If placed at the bottom
  if (nodeToTarget != NULL) {
    nodeToTarget->next = node;
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

void addNodeAtIndex(Task *task, Node *head, int index) {
  // Looking for the spot for the new node
  Node *nodeAtIndex = head;
  for (int i = 0; i < index; i++) {
    if (nodeAtIndex->next == NULL) {
      break;
    }
    nodeAtIndex = nodeAtIndex->next;
  }

  // Insert new node
  addNode(task, nodeAtIndex);
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
  Node *node = head;
  msgLog("[INFO] Printing nodes :\n   ");
  while (node->next != NULL) {
    node = node->next;
    msgLog("%s -> ", node->task.title);
  }
  msgLog("NULL\n");
  msgLog("[INFO] End of nodes\n");
}

void toggleTaskStatus(Node *node, int lineNumber) {
  node->task.isDone = node->task.isDone == 0;
}

