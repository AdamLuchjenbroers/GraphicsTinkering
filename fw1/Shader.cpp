#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <errno.h>
#include <string.h>

#include "Shader.h"
#include "logger.h"
#include <GL/glu.h>

Shader::Shader() {
    this->_shader = 0;
}

Shader::Shader(const std::string script, GLenum shadertype) {
    std::ifstream scriptFile;
    std::stringstream scriptData;
    GLenum glerror;
    GLint compileStatus;

    scriptFile.open(script.c_str());
    scriptData << scriptFile.rdbuf();

    if ( scriptFile.fail() ) {
        _shader = 0;
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_SHADERS, "Unable to open shader source file %s (%s)\n", script.c_str(), strerror(errno));
        return;
    }

    this->_shader = glCreateShader(shadertype);
    std::string scriptString = scriptData.str();
    const char *glSource = scriptString.c_str();

    glShaderSource(_shader, 1, &glSource, NULL);
    glerror = glGetError();
    if (glerror != GL_NO_ERROR) {
        glDeleteShader(_shader);
        _shader = 0;

        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_SHADERS, "glShaderSource failed to load shader: %s\n", gluErrorString(glerror));
        return;
    }

    glCompileShader(_shader);
    glerror = glGetError();
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &compileStatus);

    if (glerror != GL_NO_ERROR || compileStatus == GL_FALSE) {
        GLchar infoLog[1024];
        GLsizei infoLength;
        
        glGetShaderInfoLog(_shader, 1024, &infoLength, infoLog);
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_SHADERS, "glCompileShader failed to compile %s: %s\nLog:\n%s\n", script.c_str(), gluErrorString(glerror), infoLog);

        glDeleteShader(_shader);
        _shader = 0;
    } else {
        Logger::logprintf(Logger::LOG_INFO, Logger::LOG_SHADERS, "Successfully compiled shader: %s\n", script.c_str());
  }

};

Shader::Shader(const Shader &copy) {
    _shader = copy._shader;
}

Shader::~Shader() {
    if (_shader >= 0) {
    	glDeleteShader(_shader);
    }
};

bool Shader::isValid() {
    return (_shader > 0);
}

std::string Shader::getSource() {
  GLchar shadersource[4096];

  glGetShaderSource(_shader, 4096, NULL, shadersource);

  return std::string(shadersource);
};

GLuint Shader::getShader() {
  return _shader;
}

Shader &Shader::operator=(Shader &source) {
    _shader = source._shader;
    return *this;
};

Shader &Shader::operator=(Shader *source) {
    _shader = source->_shader;
    return *this;
}

