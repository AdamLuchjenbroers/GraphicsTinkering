#pragma once

#include <string>

#define GL_GLEXT_PROTOTYPES
#include "GL/glcorearb.h"


class VersionNumber {
public:
    virtual bool operator<(const VersionNumber &right) const;
    virtual bool operator>(const VersionNumber &right) const;
    virtual bool operator<=(const VersionNumber &right) const;
    virtual bool operator>=(const VersionNumber &right) const;

    virtual bool operator==(const VersionNumber &right) const;

    const char *getLogName() const;
protected:
    GLint major, minor;

    char logName[16];
};

class GLVersion : public VersionNumber {
public:
    GLVersion(GLint major, GLint minor);

    void printVersion();

    static GLVersion *getContextVersion();
    static GLVersion *versionFromText(char *text);
    static GLVersion *versionFromText(std::string text);

    static GLVersion *contextVersion;
};

class GLSLVersion : public VersionNumber {
public:
    GLSLVersion(GLint major, GLint minor);

    static GLSLVersion *getContextVersion();
    static GLSLVersion *versionFromText(char *text);
    static GLSLVersion *versionFromText(std::string text);

    static GLSLVersion *contextVersion;
};
