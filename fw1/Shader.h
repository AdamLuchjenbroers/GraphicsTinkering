#pragma once

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <list>
#include <string>
#include <map>

#include "config.h"

class Shader {
public:
    Shader();
    Shader(const std::string scriptfile, GLenum shadertype);
    Shader(const Shader &copy);
    ~Shader();

    std::string getSource();
    GLuint getShader();
    bool isValid();

    Shader &operator=(Shader *source);
    Shader &operator=(Shader &source);
private:
    GLuint _shader;
};
