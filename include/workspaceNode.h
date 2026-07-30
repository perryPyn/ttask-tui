#ifndef WORKSPACENODE_H
#define WORKSPACENODE_H

#include "types.h"

WorkspaceNode *createWorkspace(char name[NAME_LENGTH], TaskData *taskData);
void addWorkspaceNode(char name[NAME_LENGTH], TaskData *taskData,
                      WorkspaceNode *workspaceNodeToTarget);

#endif // !WORKSPACE_H
