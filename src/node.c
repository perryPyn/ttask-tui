#include "log.h"
#include "node.h"
#include <stdlib.h>

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
