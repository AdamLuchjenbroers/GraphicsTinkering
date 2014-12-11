#include "GLSLVersion.h"
#include "logger.h"

#include <cstdio>
#include <cstring>


GLSLVersion::GLSLVersion(GLint maj, GLint min) {
    major = maj;
    minor = min;
        
    // GLSL Minor Versions always have two digits, so presume 1.1 is meant to be 1.10
    if (minor < 10) {
        minor *= 10;
    }
  
    snprintf(logName, 16, "%i.%i", major, minor);
}

GLSLVersion::GLSLVersion(const GLSLVersion &copy) {
    major = copy.major;
    minor = copy.minor;

    strncpy(logName, copy.logName, sizeof(logName));
}

GLSLVersion *GLSLVersion::contextVersion = NULL;

GLSLVersion *GLSLVersion::getContextVersion() {
    GLint major, minor;
    char versionString[1024];


    if (contextVersion == NULL) {
        strncpy(versionString, (char *)glGetString(GL_SHADING_LANGUAGE_VERSION), 1024);

        if ( parseVersion(versionString, major, minor) ) {
            contextVersion = new GLSLVersion(major, minor);
        } else {
            Logger::logprintf(Logger::LOG_WARN, Logger::LOG_CONTEXT, "Unable to get supported GLSL version for context, defaulting to 1.3\n");
            contextVersion = new GLSLVersion(1,3);
        }
    }

    return contextVersion;
};

GLSLVersion *GLSLVersion::versionFromText(char *text) {
    GLint major, minor;

    if ( parseVersion(text, major, minor) ) {

        return new GLSLVersion(major, minor);
    } else {
        return NULL;
    }
};

GLSLVersion *GLSLVersion::versionFromText(std::string text) {
    return versionFromText(text.c_str());
}


