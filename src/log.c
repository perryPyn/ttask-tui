#include <stdio.h>
#include <stdarg.h>

void msgLog(const char *fmt, ...) {
    static FILE *log_file = NULL;
    if (!log_file) {
        log_file = fopen("app.log", "w");
    }
    
    va_list args;
    va_start(args, fmt);
    vfprintf(log_file, fmt, args);
    va_end(args);
    
    fflush(log_file);
}
