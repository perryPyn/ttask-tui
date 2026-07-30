#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "types.h"

void appendWorkspace(WorkspaceData *workspaceData, int *cursor);
void moveUpWorkspace(WorkspaceData *workspaceData, int *cursor);
void moveDownWorkspace(WorkspaceData *workspaceData, int *cursor);

#endif // !WORKSPACE_H
