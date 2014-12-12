#pragma once

#define GL_GLEXT_PROTOTYPES
#include "GL/glcorearb.h"

class VersionNumber {
public:
    virtual bool operator<(const VersionNumber &right) const;
    virtual bool operator>(const VersionNumber &right) const;
    virtual bool operator<=(const VersionNumber &right) const;
    virtual bool operator>=(const VersionNumber &right) const;

    virtual bool operator==(const VersionNumber &right) const;
    virtual bool operator!=(const VersionNumber &right) const;

    virtual VersionNumber &operator=(const VersionNumber &copy);

    const char *getLogName() const;
protected:
    GLint major, minor;

    char logName[16];

    static bool parseVersion(char *string, GLint &major, GLint &minor);
};
