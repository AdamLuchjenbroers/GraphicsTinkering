#pragma once

#include "VersionNumber.h" 

#include <string>

#define GL_GLEXT_PROTOTYPES
#include "GL/glcorearb.h"

class GLVersion : public VersionNumber {
public:
    GLVersion(GLint major, GLint minor);

    void printVersion();

    static GLVersion *getContextVersion();
    static GLVersion *versionFromText(char *text);
    static GLVersion *versionFromText(std::string text);

    static GLVersion *contextVersion;
};
