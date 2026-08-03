#ifndef WORKSPACENODE_H
#define WORKSPACENODE_H

#include "types.h"

WorkspaceNode *createWorkspace(char name[NAME_LENGTH], TaskData *taskData);
void addWorkspaceNode(char name[NAME_LENGTH], TaskData *taskData,
                      WorkspaceNode *workspaceNodeToTarget);
WorkspaceNode *appendWorkspaceNode(char name[NAME_LENGTH], TaskData *taskData,
                                   WorkspaceNode *previousWorkspace);
void removeWorkspaceNode(WorkspaceNode *node);

#endif // !WORKSPACE_H
