#include "SB6_BasicApp.h"


bool SB6_BasicApp::loadVFProgram(const char *vertexName, const char *fragmentName) {
    ShaderLibrary *lib;
    GLuint glerror;
    char shaderPath[9] = "./shader";
    bool allLoaded = true;

    ShaderLibrary::setLibraryPath(shaderPath);
    lib = ShaderLibrary::getLibrary();

    program = glCreateProgram();

    if (vertexName != NULL) {
        vertex = lib->getShader(vertexName, GL_VERTEX_SHADER);

        if (vertex != NULL) {
            glAttachShader(program, vertex->getShader());
        } else {
            Logger::logprintf(Logger::LOG_WARN, Logger::LOG_APPLICATION, "Unable to load Vertex shader %s\n", vertexName);
            allLoaded = false;
        }

    } else {
        vertex = NULL;
    }

    if (fragmentName != NULL) {
        fragment = lib->getShader(fragmentName, GL_FRAGMENT_SHADER);

        if (fragment != NULL) {
            glAttachShader(program, fragment->getShader());
        } else {
            Logger::logprintf(Logger::LOG_WARN, Logger::LOG_APPLICATION, "Unable to load Fragment shader %s\n", fragmentName);
            allLoaded = false;
        }

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

