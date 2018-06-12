#include "Logger.h"
#include <cstdarg>

void Logger::logprintf(Logger::Level loglevel, Logger::Channel logchannel, const char *format, ...) {
    va_list args;

    if (loglevel < _currentLevel[logchannel]) {
      return;
    }

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

void Logger::setLogLevel(Logger::Channel logchannel, Logger::Level loglevel) {
  _currentLevel[logchannel] = loglevel;
}
