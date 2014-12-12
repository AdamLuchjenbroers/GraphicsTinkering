#pragma once

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <list>
#include <string>
#include <map>

class Shader {
public:
    Shader();
    ~Shader();

    bool loadShader(const std::string scriptfile, GLenum shadertype);
    std::string getSource();
    GLuint getShader();
    bool isValid();

private:
    GLuint _shader;
};
