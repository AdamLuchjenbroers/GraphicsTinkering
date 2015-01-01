#pragma once

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <list>
#include <string>
#include <map>

class ShaderProgram;

class Shader {
public:
    friend class ShaderProgram;
    friend class ShaderRef;
    Shader();
    ~Shader();
    bool loadShader(const std::string scriptfile, GLenum shadertype);
    std::string getSource();
    GLuint getShader();
    bool isValid();

private:
    GLuint _shader;
    GLenum _shaderType;
};
