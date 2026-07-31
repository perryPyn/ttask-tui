#ifndef FILE_H
#define FILE_H

#include "types.h"
#include <threads.h>

int loadFile(WorkspaceData *workspaceData);
void writeFile(WorkspaceNode *WorkspaceHead);
void printTaskTable(Node *head);

#endif // !FILE_H
