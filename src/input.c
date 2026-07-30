#include "input.h"
#include "file.h"
#include "node.h"
#include "task.h"
#include "ui.h"

static void handleTaskInput(TaskData *taskData, int *cursor, int ch) {
  switch (ch) {
  case 'k':
    moveUp(taskData, cursor);
    break;
  case 'j':
    moveDown(taskData, cursor);
    break;
  case ' ':
    toggleNode(taskData->currentNode);
    writeFile(taskData->head);
    break;
  case 'a':
    appendTask(taskData, cursor);
    taskData->currentNode->task.indentation =
        taskData->currentNode->previous->task.indentation;
    writeFile(taskData->head);
    break;
  case 'A':
    appendTask(taskData, cursor);
    taskData->currentNode->task.indentation =
        taskData->currentNode->previous->task.indentation + 2;
    writeFile(taskData->head);
    break;
  case '>':
    taskData->currentNode->task.indentation =
        taskData->currentNode->task.indentation + 2;
    writeFile(taskData->head);
    break;
  case '<':
    if (taskData->currentNode->task.indentation > 0) {
      taskData->currentNode->task.indentation =
          taskData->currentNode->task.indentation - 2;
      writeFile(taskData->head);
    }
    break;
  case 'c':
    taskData->currentNode->task.status =
        (taskData->currentNode->task.status + 1) % 4;
    writeFile(taskData->head);
    break;
  case 'x': {
    removeTask(taskData, cursor);
    writeFile(taskData->head);
    break;
  }
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
      handleTaskInput(&app->taskData, &app->tasksPanel.cursor, ch);
    }
  }
}
