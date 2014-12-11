#include "VersionNumber.h"

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

bool VersionNumber::parseVersion(char *string, GLint &major, GLint &minor) {
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

    return (*loc == '.' || *loc == '\0' || *loc == ' ');
};
