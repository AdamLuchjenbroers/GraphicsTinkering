#include "Logger.h"
#include <cstdarg>

void Logger::logprintf(Logger::Level loglevel, Logger::Channel logchannel, const char *format, ...) {
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
};

