#include "input.h"
#include "file.h"
#include "node.h"
#include "task.h"
#include "types.h"
#include "ui.h"
#include "workspace.h"

static void handleTaskInput(char *filePath, WorkspaceNode *workspaceHead,
                            TaskData *taskData, int *cursor, int ch) {
  switch (ch) {
  case 'k':
    moveUp(taskData, cursor);
    break;
  case 'j':
    moveDown(taskData, cursor);
    break;
  case 'i':
    decreaseImportance(taskData);
    writeFile(workspaceHead, filePath);
    break;
  case 'u':
    increaseImportance(taskData);
    writeFile(workspaceHead, filePath);
    break;
  case ' ':
    toggleNode(taskData->currentNode);
    writeFile(workspaceHead, filePath);
    break;
  case 'a':
    appendTask(taskData, cursor);
    taskData->currentNode->task.indentation =
        taskData->currentNode->previous->task.indentation;
    writeFile(workspaceHead, filePath);
    break;
  case 'A':
    appendTask(taskData, cursor);
    taskData->currentNode->task.indentation =
        taskData->currentNode->previous->task.indentation + 2;
    writeFile(workspaceHead, filePath);
    break;
  case '>':
    taskData->currentNode->task.indentation =
        taskData->currentNode->task.indentation + 2;
    writeFile(workspaceHead, filePath);
    break;
  case '<':
    if (taskData->currentNode->task.indentation > 0) {
      taskData->currentNode->task.indentation =
          taskData->currentNode->task.indentation - 2;
      writeFile(workspaceHead, filePath);
    }
    break;
  case 'c':
    taskData->currentNode->task.status =
        (taskData->currentNode->task.status + 1) % 4;
    writeFile(workspaceHead, filePath);
    break;
  case 'x': {
    removeTask(taskData, cursor);
    writeFile(workspaceHead, filePath);
    break;
  }
  case 'm':
    renameTask(taskData->currentNode->task.title);
    writeFile(workspaceHead, filePath);
    break;
  }
}

static void handleWorkspaceInput(char *filePath, Focus *focus,
                                 WorkspaceData *workspaceData, int *cursor,
                                 int *taskCursor, int ch) {
  switch (ch) {
  case 'k':
    moveUpWorkspace(workspaceData, cursor);
    *taskCursor = 0;
    workspaceData->currentWorkspace->taskData.currentNode =
        workspaceData->currentWorkspace->taskData.head->next;
    break;
  case 'j':
    moveDownWorkspace(workspaceData, cursor);
    *taskCursor = 0;
    workspaceData->currentWorkspace->taskData.currentNode =
        workspaceData->currentWorkspace->taskData.head->next;
    break;
  case 'a':
    appendWorkspace(workspaceData, cursor);
    *focus = FOCUS_TASKS;
    *taskCursor = 0;
    writeFile(workspaceData->headWorkspace, filePath);
    break;
  case 'x':
    removeWorkspace(workspaceData, cursor);
    break;
  case 'm':
    renameTask(workspaceData->currentWorkspace->name);
    writeFile(workspaceData->headWorkspace, filePath);
    break;
  }
}

void handleInput(AppState *app, char *filePath, WINDOW *activeWin, int ch) {
  switch (ch) {
  case 'r':
    loadFile(&app->workspaceData, filePath);
    app->tasksPanel.cursor = 0;
    app->sidebarPanel.cursor = 0;
    app->workspaceData.currentWorkspace = app->workspaceData.headWorkspace;
    app->workspaceData.currentWorkspace->taskData.currentNode =
        app->workspaceData.currentWorkspace->taskData.head->next;
    renderUI(app, app->tasksPanel.win);
    break;
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
      handleTaskInput(filePath, app->workspaceData.headWorkspace,
                      &app->workspaceData.currentWorkspace->taskData,
                      &app->tasksPanel.cursor, ch);
    } else {
      handleWorkspaceInput(filePath, &app->activeFocus, &app->workspaceData,
                           &app->sidebarPanel.cursor, &app->tasksPanel.cursor,
                           ch);
    }
  }
}
