#include "logger.h"
#include <cstdarg>

void Logger::logprintf(Logger::Level loglevel, const char *format, ...) {
    va_list args;

    switch(loglevel) {
        case LOG_VERBOSEINFO:
        case LOG_INFO:
            printf("INFO: ");
            break;
        case LOG_WARN:
            printf("WARNING: ");
            break;
        case LOG_ERROR:
            printf("ERROR: ");
            break;
        default:
            printf("----: ");
    }
    
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int main() {
    Logger::logprintf(Logger::LOG_INFO, "Test message %i\n",1);
    Logger::logprintf(Logger::LOG_WARN, "Test message %i - %s\n",2, "Look, Stuff!!");
    Logger::logprintf(Logger::LOG_ERROR, "Test message %f\n",3.0f);
}
