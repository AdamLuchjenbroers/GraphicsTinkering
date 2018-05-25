#include "ShaderProgram.h"
#include "ShaderLibrary.h"
#include "Logger.h"

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>
#include <GL/glu.h>


ShaderProgram::ShaderProgram() {
    _program = 0;
    _linked = false;
}

ShaderProgram::~ShaderProgram() {
    if (_program != 0) {
        Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "Deleting GL Shader Program %i\n", _program);
        glDeleteProgram(_program);
        _program = 0;
    }
}

bool ShaderProgram::addShader(const char *name, const GLenum type) {
    ShaderLibrary *lib;
    ShaderRef newShader;

    if (_program == 0) {
        //First time this is called, create the program.
        _program = glCreateProgram();
    }

    lib = ShaderLibrary::getLibrary();
    newShader = lib->getShader(name, type);
    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "Attaching shader %s [%i] to GL Program %i\n", name, newShader.getShader(), _program);

    if (newShader.isValid()) {
        _shaders.push_back( newShader );

        return true;
    } else {
        return false;
    }
}

void ShaderProgram::bindAttribute(const GLchar *attrib, GLuint location) {
    glBindAttribLocation(_program, location, attrib);
}

void ShaderProgram::clearProgram() {
    if (_program != 0) {
        Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "Deleting GL Shader Program %i\n", _program);
        glDeleteProgram(_program);
        _program = 0;

        _shaders.clear(); 
    }
    _linked = false;
}

bool ShaderProgram::linkProgram() {
    std::list<ShaderRef>::iterator itr;
    GLuint glerror;
    GLint linkState;

    for (itr = _shaders.begin(); itr != _shaders.end(); itr++) {
        GLuint shader = itr->getShader();

        glAttachShader(_program, shader);

        glerror = glGetError();
        if (glerror != GL_NO_ERROR) {
            Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_SHADERS, "Unable to attach shader [%i], error: %s\n", shader, gluErrorString(glerror));
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

bool ShaderProgram::isLinked() {
    return _linked;
}

GLint ShaderProgram::uniformLocation(const GLchar *uniform) {
    if ( _linked ) {
        return glGetUniformLocation( _program, uniform );
    } else {
        return -1;
    }
}

GLint ShaderProgram::uniformBlockLocation(const GLchar *uniform) {
    if ( _linked ) {
        return glGetUniformBlockIndex( _program, uniform );
    } else {
        return -1;
    }
}


GLint ShaderProgram::attributeLocation(const GLchar *name) {
  return glGetAttribLocation(_program, name);
}

GLuint ShaderProgram::programID() {
    if ( _linked ) {
        return _program;
    } else {
        return -1;
    }
}
