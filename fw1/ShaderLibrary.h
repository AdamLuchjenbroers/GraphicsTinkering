#pragma once

#include "fw1.h"

#include <map>

class ShaderLibrary {
public:
    Shader *getShader(const char *name, GLuint stage);

    static ShaderLibrary *getLibrary();
    static void setLibraryPath(char *newpath);
private:
    static ShaderLibrary *library;

    ShaderLibrary(char *basepath);

    std::map<GLSLVersion, char*> versions;
};
