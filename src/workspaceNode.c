#include "workspaceNode.h"
#include "log.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>

WorkspaceNode *createWorkspace(char name[NAME_LENGTH], TaskData *taskData) {
  WorkspaceNode *workspaceNode = NULL;
  workspaceNode = (WorkspaceNode *)malloc(sizeof(WorkspaceNode));

  if (!workspaceNode) {
    msgLog("[CRIT] Memory allocation failed\n");
    return NULL;
  }

  strncpy(workspaceNode->name, name, NAME_LENGTH - 1);
  workspaceNode->taskData = *taskData;
  workspaceNode->previous = NULL;
  workspaceNode->next = NULL;

  return workspaceNode;
}

void addWorkspaceNode(char name[NAME_LENGTH], TaskData *taskData,
                      WorkspaceNode *workspaceNodeToTarget) {
  WorkspaceNode *workspaceNode = createWorkspace(name, taskData);

  workspaceNode->previous = workspaceNodeToTarget;
  workspaceNode->next = workspaceNodeToTarget->next;

  // If placed at the top
  if (workspaceNodeToTarget->next != NULL) {
    workspaceNodeToTarget->next->previous = workspaceNode;
  }
  // If placed at the bottom
  if (workspaceNodeToTarget != NULL) {
    workspaceNodeToTarget->next = workspaceNode;
  }
}

WorkspaceNode *appendWorkspaceNode(char name[NAME_LENGTH], TaskData *taskData,
                                   WorkspaceNode *previousWorkspace) {
  WorkspaceNode *workspaceNode = createWorkspace(name, taskData);

  workspaceNode->previous = previousWorkspace;
  workspaceNode->next = NULL;

  previousWorkspace->next = workspaceNode;
  return workspaceNode;
}

void removeWorkspaceNode(WorkspaceNode *node) {
  if (node == NULL) {
    return;
  }

  Node *currentNode = node->taskData.head;
  while (currentNode != NULL) {
    Node *nextNode = currentNode->next;
    free(currentNode);
    currentNode = nextNode;
  }

  if (node->previous != NULL) {
    node->previous->next = node->next;
  }
  if (node->next != NULL) {
    node->next->previous = node->previous;
  }

  free(node);
}
