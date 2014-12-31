#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <errno.h>
#include <string.h>

#include "Shader.h"
#include "Logger.h"
#include <GL/glu.h>

Shader::Shader() {
    _shader = 0;
}

bool Shader::loadShader(const std::string script, GLenum shadertype) {
    std::ifstream scriptFile;
    std::stringstream scriptData;
    GLenum glerror;
    GLint compileStatus;

    scriptFile.open(script.c_str());
    scriptData << scriptFile.rdbuf();

    if ( _shader != 0 ) {
        //Release the previous shader
        glDeleteShader(_shader);
    }

    if ( scriptFile.fail() ) {
        _shader = 0;
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_SHADERS, "Unable to open shader source file %s (%s)\n", script.c_str(), strerror(errno));
        return false;
    }

    _shader = glCreateShader(shadertype);
    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "Loading %s to GL shader %i\n", script.c_str(), _shader); 

    std::string scriptString = scriptData.str();
    const char *glSource = scriptString.c_str();

    glShaderSource(_shader, 1, &glSource, NULL);
    glerror = glGetError();
    if (glerror != GL_NO_ERROR) {
        glDeleteShader(_shader);
        _shader = 0;

        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_SHADERS, "glShaderSource failed to load shader: %s\n", gluErrorString(glerror));
        return false;
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
        return false;
    } else {
        Logger::logprintf(Logger::LOG_INFO, Logger::LOG_SHADERS, "Successfully compiled shader [%i]: %s\n", _shader, script.c_str());
        return true;
    }

};

Shader::~Shader() {
    if (_shader >= 0) {
        Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "Releasing shader %i\n", _shader); 
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

