#include "SB6_BasicApp.h"


void SB6_BasicApp::loadShaders(const char *vertexName, const char *fragmentName) {
    ShaderLibrary *lib;
    GLuint glerror;
    char shaderPath[9] = "./shader";

    ShaderLibrary::setLibraryPath(shaderPath);
    lib = ShaderLibrary::getLibrary();

    program = glCreateProgram();

    if (vertexName != NULL) {
        vertex = lib->getShader(vertexName, GL_VERTEX_SHADER); 
        glAttachShader(program, vertex->getShader());
    } else {
        vertex = NULL;
    }

    if (fragmentName != NULL) {
        fragment = lib->getShader("sb2-fragment.sdr", GL_FRAGMENT_SHADER); 
        glAttachShader(program, fragment->getShader());
    } else { 
        fragment = NULL;
    }
    
    glLinkProgram(program);
   
    glerror = glGetError();
    if (glerror != GL_NO_ERROR) {
         Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Unable to link rendering program: %s\n", gluErrorString(glerror));
    }

    glUseProgram(program);
};

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
  
   if (vertex != NULL) {
       delete vertex;
   }

   if (fragment != NULL) {
       delete fragment;
   }
}

