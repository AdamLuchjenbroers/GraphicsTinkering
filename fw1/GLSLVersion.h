#pragma once

#include "VersionNumber.h" 

#include <string>

#define GL_GLEXT_PROTOTYPES
#include "GL/glcorearb.h"

class GLSLVersion : public VersionNumber {
public:
    GLSLVersion(GLint major, GLint minor);
    GLSLVersion(const GLSLVersion &copy);

    static GLSLVersion getContextVersion();
    static GLSLVersion versionFromText(char *text);
    static GLSLVersion versionFromText(std::string text);
};
