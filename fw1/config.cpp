#include "config.h"

#include <cstdio>
#include <cstring>

inline bool VersionNumber::operator<(const VersionNumber &right) {
  if (this->major < right.major) return true;
  if ((this->major == right.major) && (this->minor < right.minor)) return true;
  return false; 
}

inline bool VersionNumber::operator>(const VersionNumber &right) {
  if (this->major > right.major) return true;
  if ((this->major == right.major) && (this->minor > right.minor)) return true;
  return false; 
}

inline bool VersionNumber::operator>=(const VersionNumber &right) {
  return !(*this < right);
}

inline bool VersionNumber::operator<=(const VersionNumber &right) {
  return !(*this > right);
}

inline bool VersionNumber::operator==(const VersionNumber &right) {
  return (this->major == right.major && this->minor == right.minor);
}

GLVersion::GLVersion(GLint maj, GLint min) {
  major = maj;
  minor = min;
}

GLVersion *GLVersion::getContextVersion() {
    GLint major, minor;

    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    return new GLVersion(major, minor);
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
}

GLSLVersion *GLSLVersion::getContextVersion() {
    GLint major, minor;
    char versionString[1024];

    strncpy(versionString, (char *)glGetString(GL_SHADING_LANGUAGE_VERSION), 1024);
    if ( parseVersion(versionString, major, minor) ) {
        return new GLSLVersion(major, minor);
    }
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


