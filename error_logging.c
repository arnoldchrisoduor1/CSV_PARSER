#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

typedef enum
{
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL
} LogLevel;

void log_message(LogLevel level, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    //Determine the appropriate log prefix
    const char* levelPrefix;

    switch (level)
    {
        case LOG_DEBUG:
            levelPrefix = "[DEBUG]";
            break;
        case LOG_INFO:
            levelPrefix = "[INFO]";
            break;
        case LOG_WARNING:
            levelPrefix = "[WARNING]";
            break;
        case LOG_ERROR:
            levelPrefix = "[ERROR]";
            break;
        case LOG_CRITICAL:
            levelPrefix = "[CRITICAL]";
            break;
        default:
            levelPrefix = "";
            break;
    }

    //Format and print the log message
    printf("%s", levelPrefix);
    vprintf(format, args);
    printf("\n");

    va_end(args);
}
int main(int argc, char* argv[])
{
    puts("");
    log_message(LOG_INFO, " This is an informational message.");
    log_message(LOG_WARNING, " Invalid input detected.");
    log_message(LOG_ERROR, " Unable to open file '%s'","data.txt.");
    puts("");

    return 0;
}