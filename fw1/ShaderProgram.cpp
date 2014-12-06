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
    Shader *newShader;

    lib = ShaderLibrary::getLibrary();

    if (_program == 0) {
        //First time this is called, create the program.
        _program = glCreateProgram();
    }

    newShader = lib->getShader(name, type);

    if (newShader != NULL) {
        _shaders[type] = newShader;
        delete newShader;

        return true;
    } else {
        return false;
    }
}

bool ShaderProgram::linkProgram() {
    std::map<GLenum, Shader>::iterator itr;
    GLuint glerror;

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
