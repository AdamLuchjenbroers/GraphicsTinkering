#include "SB6_BasicApp.h"


bool SB6_BasicApp::loadVFProgram(const char *vertexName, const char *fragmentName) {
    ShaderLibrary *lib;
    GLuint glerror;
    char shaderPath[9] = "./shader";
    bool success = true;

    ShaderLibrary::setLibraryPath(shaderPath);

    success = program.addShader(vertexName, GL_VERTEX_SHADER);
    success &= program.addShader(fragmentName, GL_FRAGMENT_SHADER);

    if (success == false) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Failed to build shader program, missing shader\n");

        return false;
    }

    success = program.linkProgram();

    if (success == false) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Unable to link rendering program: %s\n", gluErrorString(glerror));

        return false;
    }
    
    glUseProgram(program.programID());

    return success;
};

bool SB6_BasicApp::linkProgram() {
    return program.linkProgram();
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


SB6_BasicApp::~SB6_BasicApp() {
   if (display != NULL) {
       delete display;
   }
}

