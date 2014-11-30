#include "config.h"

#include <cstdio>

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

GLVersion::GLVersion() {
  glGetIntegerv(GL_MAJOR_VERSION, &major);
  glGetIntegerv(GL_MINOR_VERSION, &minor);
}

void GLVersion::printVersion() {
    printf("%i.%i\n",major, minor);
}

GLVersion *GLVersion::versionFromText(char *text) {
    GLint major, minor;

    major = 0;
    while (*text >= '0' && *text <= '9') {
        major *= 10;
        major += *text - '0';
        text++;
    }
   
    if (*text != '.' || major == 0) {
        return NULL;
    }
    text++;

    minor = 0;
    while (*text >= '0' && *text <= '9') {
        minor *= 10;
        minor += *text - '0';
        text++;
    }

    if (*text == '.' || *text == '\0') {
        return new GLVersion(major, minor);
    } else {
        return NULL;
    }
}


