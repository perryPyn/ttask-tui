#include "config.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define DEFAULT_CONFIG_PATH "~/.config/ttask/ttask.conf"
#define DEFAULT_FILE_PATH   "~/.config/ttask/task.md"

static void expandPath(const char *input, char *output, size_t maxLen) {
    if (input == NULL || output == NULL || maxLen == 0) {
        return;
    }

    if (input[0] == '~') {
        const char *home = getenv("HOME");
        if (home != NULL) {
            snprintf(output, maxLen, "%s%s", home, input + 1);
        } else {
            snprintf(output, maxLen, "%s", input);
        }
    } else {
        snprintf(output, maxLen, "%s", input);
    }
}

static AppConfig initDefaultConfig(void) {
    AppConfig appConfig;

    if (getenv("HOME") == NULL) {
        msgLog("[WARN] $HOME variable not set, using relative path fallback");
    }

    expandPath(DEFAULT_CONFIG_PATH, appConfig.confPath, sizeof(appConfig.confPath));
    expandPath(DEFAULT_FILE_PATH, appConfig.filePath, sizeof(appConfig.filePath));

    return appConfig;
}

void initConfig() {
  AppConfig appConfig = initDefaultConfig();
  FILE *fptr = fopen(appConfig.confPath, "r");
  if (fptr == NULL) {
    msgLog("[WARN] No config file found, using default");
    return;
  }

  char line[256];
  while (fgets(line, sizeof(line), fptr) != NULL) {
    line[strcspn(line, "\r\n")] = '\0';

    if (line[0] == '#' || line[0] == ';' || line[0] == '\0') {
      continue;
    }

    char *sep = strchr(line, '=');
    if (sep == NULL) {
      continue;
    }

    *sep = '\0';

    char *key = line;
    char *val = sep + 1;

    while (*val == ' ' || *val == '\t') {
      val++;
    }

    if (strcmp(key, "file_path") == 0) {
      expandPath(val, appConfig.filePath, sizeof(appConfig.filePath));
    }
  }
}
