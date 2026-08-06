#include "task.h"
#include "log.h"
#include "node.h"
#include "types.h"
#include "utils.h"
#include <ncurses.h>
#include <string.h>

void appendTask(TaskData *taskData, int *cursor) {
  if (taskData == NULL || taskData->head == NULL)
    return;

  char title[TITLE_LENGTH] = "";
  if (!promptString("New Task", title, TITLE_LENGTH)) {
    return;
  }

  bool wasEmpty = (taskData->currentNode == NULL);
  Node *targetNode = wasEmpty ? taskData->head : taskData->currentNode;

  Task task = {0, 0, 0, ""};
  cpyStr(task.title, title, TITLE_LENGTH);

  addNode(&task, targetNode);
  taskData->length++;
  taskData->currentNode = targetNode->next;

  *cursor = wasEmpty ? 0 : (*cursor + 1);
}

void removeTask(TaskData *taskData, int *cursor) {
  if (taskData->currentNode == NULL) {
    msgLog("[WARN] current node is NULL");
    return;
  }
  Node *toDelete = taskData->currentNode;

  if (taskData->currentNode->next == NULL) {
    taskData->currentNode = taskData->currentNode->previous;
    (*cursor)--;
  } else {
    taskData->currentNode = taskData->currentNode->next;
  }

  removeNode(toDelete);
  taskData->length -= 1;
}

void moveUp(TaskData *taskData, int *cursor) {
  if (taskData->currentNode == NULL) {
    return;
  }
  if (taskData->currentNode->previous != NULL &&
      taskData->currentNode->previous->previous != NULL) {
    taskData->currentNode = taskData->currentNode->previous;
    (*cursor)--;
  }
}

void moveDown(TaskData *taskData, int *cursor) {
  if (taskData->currentNode == NULL) {
    return;
  }
  if (taskData->currentNode->next != NULL) {
    taskData->currentNode = taskData->currentNode->next;
    (*cursor)++;
  }
}

void increaseImportance(TaskData *taskData) {
  if (taskData->currentNode == NULL) {
    return;
  }
  if (taskData->currentNode->task.importance < 3) {
    (taskData->currentNode->task.importance)++;
  }
}

void decreaseImportance(TaskData *taskData) {
  if (taskData->currentNode == NULL) {
    return;
  }
  if (taskData->currentNode->task.importance > 0) {
    (taskData->currentNode->task.importance)--;
  }
}

void renameTask(char title[TITLE_LENGTH]) {
  char newTitle[TITLE_LENGTH] = "";

  if (promptString("New Title", newTitle, TITLE_LENGTH)) {
    cpyStr(title, newTitle, TITLE_LENGTH);
  }
}
