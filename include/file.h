#ifndef FILE_H
#define FILE_H

#include "types.h"

int loadFile(WorkspaceData *workspaceData, char *filePath);
void writeFile(WorkspaceNode *WorkspaceHead, char *filePath);
void printTaskTable(Node *head);

#endif // !FILE_H
