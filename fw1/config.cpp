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

