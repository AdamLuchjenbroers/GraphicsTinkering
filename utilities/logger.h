#include <stdio.h>

namespace Logger {
    enum Level {
        LOG_VERBOSEINFO  
    ,   LOG_INFO
    ,   LOG_WARN
    ,   LOG_ERROR
    };

    enum Channel {
        LOG_SHADERS
    };

  void logprintf(Level loglevel, Channel logchannel, const char *format, ...);
}
