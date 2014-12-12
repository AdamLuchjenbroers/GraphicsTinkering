#include "SB6_BasicApp.h"


bool SB6_BasicApp::loadVFProgram(const char *vertexName, const char *fragmentName) {
    GLuint glerror;
    bool success = true;

    ShaderLibrary::setLibraryPath("./shader");

    success = program.addShader(vertexName, GL_VERTEX_SHADER);
    success &= program.addShader(fragmentName, GL_FRAGMENT_SHADER);

    if (success == false) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Failed to build shader program, missing shader\n");

        return false;
    }

    // Use explicit location bindings compatibility with older GLSL versions
    program.bindAttribute("position", 0);
    program.bindAttribute("offset", 1);
    program.bindAttribute("color", 2);

    success = program.linkProgram();

    if (success == false) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Unable to link rendering program: %s\n", gluErrorString(glerror));

        return false;
    }
    
    glUseProgram(program.programID());

    return success;
};

bool SB6_BasicApp::loadShader(const char *shaderName, const GLenum shaderType) {
    bool success = program.addShader(shaderName, shaderType);

    if (success == false) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Failed to build compile shader %s\n", shaderName);
        return false;
    }
    return true;
}

bool SB6_BasicApp::linkProgram() {
    bool success = program.linkProgram();

    if (success == false) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Failed to link shader program\n");
        return false;
    }
    return true;
}

void SB6_BasicApp::appQuit() {
    running = false;
};

void SB6_BasicApp::valueSwing(GLfloat &offset, GLfloat increment, bool &increase, GLfloat min, GLfloat max) {
    if (increase) {
        offset += increment;
    } else {
        offset -= increment;
    }

    if (offset >= max || offset <= min) {
        increase = !increase;
    }
};

bool SB6_BasicApp::checkGLError(const char *errfmt, Logger::Level loglevel) {
    GLenum glerror;

    glerror = glGetError();

    if (glerror == GL_NO_ERROR) {
       return true;
    } else {
       Logger::logprintf(loglevel, Logger::LOG_APPLICATION, errfmt, gluErrorString(glerror));
       return false;
    }
}

SB6_BasicApp::~SB6_BasicApp() {
   if (display != NULL) {
       delete display;
   }
}

