#include "config.h"
#include "log.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define DEFAULT_CONFIG_PATH "~/.config/ttask/ttask.conf"
#define DEFAULT_FILE_PATH "~/.config/ttask/task.md"

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

static int hexToShort(short id, const char *hex) {
  // Check if terminal is capable
  if (!can_change_color()) {
    return -1;
  }

  if (hex[0] == '#') {
    hex++;
  }

  unsigned int r, g, b;
  if (sscanf(hex, "%02x%02x%02x", &r, &g, &b) != 3) {
    return -1; // hex format incorrect
  }

  // Conversion
  short nr = (short)((r * 1000) / 255);
  short ng = (short)((g * 1000) / 255);
  short nb = (short)((b * 1000) / 255);

  return init_color(id, nr, ng, nb);
}

static AppConfig initDefaultConfig(void) {
  AppConfig appConfig;

  if (getenv("HOME") == NULL) {
    msgLog("[WARN] $HOME variable not set, using relative path fallback\n");
  }

  expandPath(DEFAULT_CONFIG_PATH, appConfig.confPath,
             sizeof(appConfig.confPath));
  expandPath(DEFAULT_FILE_PATH, appConfig.filePath, sizeof(appConfig.filePath));

  return appConfig;
}

AppConfig initConfig() {
  AppConfig appConfig = initDefaultConfig();
  FILE *fptr = fopen(appConfig.confPath, "r");
  if (fptr == NULL) {
    msgLog("[WARN] Tried to find config file at : %s\n", appConfig.confPath);
    msgLog("[WARN] No config file found, using default\n");
    return appConfig; // Will have default values
  }
  msgLog("[INFO] Found config file at %s\n", appConfig.confPath);

  // Parser
  char line[256];
  while (fgets(line, sizeof(line), fptr) != NULL) {
    line[strcspn(line, "\r\n")] = '\0';

    // Skip comments and empty lines
    if (line[0] == '#' || line[0] == ';' || line[0] == '\0') {
      continue;
    }

    // Lokking for the '=' separator
    char *sep = strchr(line, '=');
    if (sep == NULL) {
      continue;
    }

    *sep = '\0'; // Replace '=' by line separator
    char *key = line;
    char *val = sep + 1;

    // Skip spaces
    while (*val == ' ' || *val == '\t') {
      val++;
    }

    /*--- Update variables ---*/
    if (strcmp(key, "file") == 0) {
      expandPath(val, appConfig.filePath, sizeof(appConfig.filePath));
    }
    if (strcmp(key, "base02") == 0) {
      hexToShort(16, val);
    }
    if (strcmp(key, "base08") == 0) {
      hexToShort(17, val);
    }
    if (strcmp(key, "base0A") == 0) {
      hexToShort(18, val);
    }
    if (strcmp(key, "base0B") == 0) {
      hexToShort(19, val);
    }
  }
  return appConfig;
}
