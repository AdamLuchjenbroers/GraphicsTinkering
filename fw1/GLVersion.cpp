#include "GLVersion.h"
#include "logger.h"

#include <cstdio>
#include <cstring>

GLVersion::GLVersion(GLint maj, GLint min) {
    major = maj;
    minor = min;

    snprintf(logName, 16, "%i.%i", major, minor);
}

GLVersion::GLVersion(const GLVersion &copy) {
    major = copy.major;
    minor = copy.minor;
  
    snprintf(logName, 16, "%i.%i", major, minor);
}

GLVersion GLVersion::getContextVersion() {
    GLint major, minor;

    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    return GLVersion(major, minor);
}

void GLVersion::printVersion() {
    printf("%i.%i\n",major, minor);
}


GLVersion GLVersion::versionFromText(char *text) {
    GLint major, minor;

    if ( parseVersion(text, major, minor) ) {
        return GLVersion(major, minor);
    } else {
        //TODO: Throw exception
        return GLVersion(0,0);
    }
};

GLVersion GLVersion::versionFromText(std::string text) {
    return versionFromText(text.c_str());
}
