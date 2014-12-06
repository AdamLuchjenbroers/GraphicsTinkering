#include "config.h"
#include "logger.h"

#include <cstdio>
#include <cstring>

inline bool VersionNumber::operator<(const VersionNumber &right) const {
  if (this->major < right.major) return true;
  if ((this->major == right.major) && (this->minor < right.minor)) return true;
  return false; 
}

inline bool VersionNumber::operator>(const VersionNumber &right) const {
  if (this->major > right.major) return true;
  if ((this->major == right.major) && (this->minor > right.minor)) return true;
  return false; 
}

inline bool VersionNumber::operator>=(const VersionNumber &right) const {
  return !(*this < right);
}

inline bool VersionNumber::operator<=(const VersionNumber &right) const {
  return !(*this > right);
}

inline bool VersionNumber::operator==(const VersionNumber &right) const {
  return (this->major == right.major && this->minor == right.minor);
}

const char *VersionNumber::getLogName() const {
    return logName;
}

GLVersion::GLVersion(GLint maj, GLint min) {
  major = maj;
  minor = min;

  snprintf(logName, 16, "%i.%i", major, minor);
}

GLVersion *GLVersion::contextVersion = NULL;

GLVersion *GLVersion::getContextVersion() {
    GLint major, minor;

    if (contextVersion == NULL) {
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);

        contextVersion = new GLVersion(major, minor);
    }

    return contextVersion;
}

void GLVersion::printVersion() {
    printf("%i.%i\n",major, minor);
}

bool parseVersion(char *string, GLint &major, GLint &minor) {
    char *loc = string;

    major = 0;
    while (*loc >= '0' && *loc <= '9') {
        major *= 10;
        major += *loc - '0';
        loc++;
    }
   
    if (*loc != '.' || major == 0) {
        return false;
    }
    loc++;

    minor = 0;
    while (*loc >= '0' && *loc <= '9') {
        minor *= 10;
        minor += *loc - '0';
        loc++;
    }

    return (*loc == '.' || *loc == '\0');  
};

GLVersion *GLVersion::versionFromText(char *text) {
    GLint major, minor;

    if ( parseVersion(text, major, minor) ) {
        return new GLVersion(major, minor);
    } else {
        return NULL;
    }
};

GLVersion *GLVersion::versionFromText(std::string text) {
    return versionFromText(text.c_str());
}


GLSLVersion::GLSLVersion(GLint maj, GLint min) {
    major = maj;
    minor = min;
        
    // GLSL Minor Versions always have two digits, so presume 1.1 is meant to be 1.10
    if (minor < 10) {
        minor *= 10;
    }
  
    snprintf(logName, 16, "%i.%i", major, minor);
}

GLSLVersion *GLSLVersion::contextVersion = NULL;

GLSLVersion *GLSLVersion::getContextVersion() {
    GLint major, minor;
    char versionString[1024];


    if (contextVersion == NULL) {
        strncpy(versionString, (char *)glGetString(GL_SHADING_LANGUAGE_VERSION), 1024);

        if ( parseVersion(versionString, major, minor) ) {
            contextVersion = new GLSLVersion(major, minor);
        } else {
            Logger::logprintf(Logger::LOG_WARN, Logger::LOG_CONTEXT, "Unable to get supported GLSL version for context, defaulting to 1.3\n");
            contextVersion = new GLSLVersion(1,3);
        }
    }

    return contextVersion;
};

GLSLVersion *GLSLVersion::versionFromText(char *text) {
    GLint major, minor;

    if ( parseVersion(text, major, minor) ) {

        return new GLSLVersion(major, minor);
    } else {
        return NULL;
    }
};

GLSLVersion *GLSLVersion::versionFromText(std::string text) {
    return versionFromText(text.c_str());
}


