#include <stdio.h>

namespace Logger {
    enum Level {
        LOG_VERBOSEINFO  
    ,   LOG_INFO
    ,   LOG_WARN
    ,   LOG_ERROR
    };

  void logprintf(Level loglevel, const char *format, ...);
}
