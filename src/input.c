#include "input.h"
#include "file.h"
#include "node.h"
#include "task.h"
#include "types.h"
#include "ui.h"
#include "workspace.h"

static void handleTaskInput(WorkspaceNode *workspaceHead, TaskData *taskData,
                            int *cursor, int ch) {
  switch (ch) {
  case 'k':
    moveUp(taskData, cursor);
    break;
  case 'j':
    moveDown(taskData, cursor);
    break;
  case ' ':
    toggleNode(taskData->currentNode);
    writeFile(workspaceHead);
    break;
  case 'a':
    appendTask(taskData, cursor);
    taskData->currentNode->task.indentation =
        taskData->currentNode->previous->task.indentation;
    writeFile(workspaceHead);
    break;
  case 'A':
    appendTask(taskData, cursor);
    taskData->currentNode->task.indentation =
        taskData->currentNode->previous->task.indentation + 2;
    writeFile(workspaceHead);
    break;
  case '>':
    taskData->currentNode->task.indentation =
        taskData->currentNode->task.indentation + 2;
    writeFile(workspaceHead);
    break;
  case '<':
    if (taskData->currentNode->task.indentation > 0) {
      taskData->currentNode->task.indentation =
          taskData->currentNode->task.indentation - 2;
      writeFile(workspaceHead);
    }
    break;
  case 'c':
    taskData->currentNode->task.status =
        (taskData->currentNode->task.status + 1) % 4;
    writeFile(workspaceHead);
    break;
  case 'x': {
    removeTask(taskData, cursor);
    writeFile(workspaceHead);
    break;
  }
  }
}

static void handleWorkspaceInput(Focus *focus, WorkspaceData *workspaceData,
                                 int *cursor, int *taskCursor, int ch) {
  switch (ch) {
  case 'k':
    moveUpWorkspace(workspaceData, cursor);
    *taskCursor = 0;
    break;
  case 'j':
    moveDownWorkspace(workspaceData, cursor);
    *taskCursor = 0;
    break;
  case 'a':
    appendWorkspace(workspaceData, cursor);
    *focus = FOCUS_TASKS;
    *taskCursor = 0;
    // writeFile(taskData->head);
    break;
  }
}

void handleInput(AppState *app, WINDOW *activeWin, int ch) {
  switch (ch) {
  case KEY_RESIZE:
    resizeterm(0, 0);
    clear();
    destWin(app);
    initWin(app);
    break;
  case '\t': {
    if (app->activeFocus == FOCUS_TASKS) {
      app->activeFocus = FOCUS_SIDEBAR;
    } else {
      app->activeFocus = FOCUS_TASKS;
    }
    break;
  }
  case 'q':
    app->isRunning = 0;
    break;
  default:
    if (app->activeFocus == FOCUS_TASKS) {
      handleTaskInput(app->workspaceData.headWorkspace,
                      &app->workspaceData.currentWorkspace->taskData,
                      &app->tasksPanel.cursor, ch);
    } else {
      handleWorkspaceInput(&app->activeFocus, &app->workspaceData,
                           &app->sidebarPanel.cursor, &app->tasksPanel.cursor,
                           ch);
    }
  }
}
