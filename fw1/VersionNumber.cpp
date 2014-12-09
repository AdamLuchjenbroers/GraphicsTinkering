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
