#include "utils.h"
#include <stddef.h>
#include <string.h>
#include "task.h"

void cpyStr(char *dest, const char *src) {
    size_t len = strlen(src);
    if (len >= TITLE_LENGTH) {
        len = TITLE_LENGTH - 1;
    }
    memcpy(dest, src, len);
    dest[len] = '\0';
}

