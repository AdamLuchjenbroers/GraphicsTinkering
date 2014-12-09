#include "ShaderProgram.h"
#include "logger.h"

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>
#include <GL/glu.h>


ShaderProgram::ShaderProgram() {
    _program = 0;
    _linked = false;
}

ShaderProgram::~ShaderProgram() {

}

bool ShaderProgram::addShader(const char *name, const GLenum type) {
    ShaderLibrary *lib;
    ShaderRef newShader;

    lib = ShaderLibrary::getLibrary();

    if (_program == 0) {
        //First time this is called, create the program.
        _program = glCreateProgram();
    }

    newShader = lib->getShader(name, type);

    if (newShader.isValid()) {
        _shaders[type] = newShader;

        return true;
    } else {
        return false;
    }
}

bool ShaderProgram::linkProgram() {
    std::map<GLenum, ShaderRef>::iterator itr;
    GLuint glerror;
    GLint linkState;

    for (itr = _shaders.begin(); itr != _shaders.end(); itr++) {
        GLuint shader = itr->second.getShader();

        glAttachShader(_program, shader);

        glerror = glGetError();
        if (glerror != GL_NO_ERROR) {
            Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_SHADERS, "Unable to attach shader, error: %s\n", gluErrorString(glerror));
            return false;
        }
    }

    glLinkProgram(_program);

    glerror = glGetError();
    if (glerror != GL_NO_ERROR) {
         Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_SHADERS, "Unable to link rendering program: %s\n", gluErrorString(glerror));
         return false;
    }

    glGetProgramiv(_program, GL_LINK_STATUS, &linkState);
    if (linkState != GL_TRUE) {
        GLsizei logLength;
        GLchar log[1024];

        glGetProgramInfoLog(_program, 1024, &logLength, log);
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_SHADERS, "Linking of shader program %i failed\n---------\n%s\n---------\n", _program, log);

        return false;
    }

    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_SHADERS, "Successfully linked Shader Program %i\n", _program);
    _linked = true;
    return true;
}

GLuint ShaderProgram::programID() {
    if ( _linked ) {
        return _program;
    } else {
        return -1;
    }
}
