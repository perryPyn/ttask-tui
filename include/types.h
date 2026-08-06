#ifndef TYPES_H
#define TYPES_H

#include <ncurses.h>

/*---Macro---*/
#define TITLE_LENGTH 64
#define NAME_LENGTH 16
#define TABLE_LENGTH 256

/*--Enum---*/
typedef enum {
  TASK_TODO = 0,
  TASK_IN_PROGRESS,
  TASK_DONE,
  TASK_ON_HOLD,
  TASK_COUNT
} TaskStatus;

typedef enum { FOCUS_TASKS, FOCUS_SIDEBAR } Focus;

/*---Struct---*/
typedef struct {
  int indentation;
  int status;
  int importance;
  char title[TITLE_LENGTH];
  // char description[512];
} Task;

typedef struct Node {
  Task task;
  struct Node *next;
  struct Node *previous;
} Node;

typedef struct {
  WINDOW *win;
  WINDOW *content;
  int cursor;
  // int scrollOffset;
} Panel;

typedef struct {
  Node *head;
  Node *currentNode;
  int length;
} TaskData;

typedef struct WorkspaceNode {
  char name[16];
  TaskData taskData;
  struct WorkspaceNode *previous;
  struct WorkspaceNode *next;
} WorkspaceNode;

typedef struct {
  WorkspaceNode *headWorkspace;
  WorkspaceNode *currentWorkspace;
  int length;
} WorkspaceData;

typedef struct {
  bool isRunning;
  Focus activeFocus;
  Panel sidebarPanel;
  Panel tasksPanel;
  WorkspaceData workspaceData;
} AppState;

#endif // !TYPES_H
