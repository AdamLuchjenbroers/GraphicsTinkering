#pragma once

#include <stdio.h>

#include <map>

namespace Logger {
    enum Level {
        LOG_VERBOSEINFO  
    ,   LOG_INFO
    ,   LOG_WARN
    ,   LOG_ERROR
    };

    enum Channel {
        LOG_SHADERS
    ,   LOG_TEXTURES
    ,   LOG_MESHES
    ,   LOG_LIGHTING
    ,   LOG_APPLICATION
    ,   LOG_CONTEXT
    };

  void logprintf(Level loglevel, Channel logchannel, const char *format, ...);

  void setLogLevel(Channel logchannel, Level loglevel);

  // Wrap private state in an anonymous namespace:
  namespace {
    std::map<Channel, Level> _currentLevel = {
      { LOG_SHADERS     , LOG_WARN }
    , { LOG_TEXTURES    , LOG_WARN }
    , { LOG_MESHES      , LOG_WARN }
    , { LOG_LIGHTING    , LOG_WARN }
    , { LOG_APPLICATION , LOG_INFO }
    , { LOG_CONTEXT     , LOG_WARN }
    };
  }
}
