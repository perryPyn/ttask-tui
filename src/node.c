#include "node.h"
#include "log.h"
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
  if (nodeToTarget == NULL || task == NULL) {
    msgLog("[WARN] Cannot add node: target or task is NULL\n");
    return;
  }

  Node *node = createNode(task);
  if (node == NULL) {
    msgLog("[CRIT] Memory allocation failed for new node\n");
    return;
  }

  node->previous = nodeToTarget;
  node->next = nodeToTarget->next;

  if (nodeToTarget->next != NULL) {
    nodeToTarget->next->previous = node;
  }

  nodeToTarget->next = node;
}

Node *appendNode(Task *task, Node *previousNode) {
  Node *node = createNode(task);

  node->previous = previousNode;
  node->next = NULL;

  previousNode->next = node;
  return node;
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

void printNodes(Node *head) {
  Node *node = head;
  msgLog("[INFO] Printing nodes :\n\t");
  while (node->next != NULL) {
    node = node->next;
    msgLog("%s -> ", node->task.title);
  }
  msgLog("NULL\n");
  msgLog("[INFO] End of nodes\n");
}

void toggleNode(Node *node) {
  node->task.status = (node->task.status != 0) ? 0 : 2;
}
