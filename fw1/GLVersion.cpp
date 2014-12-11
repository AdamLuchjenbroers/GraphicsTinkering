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

GLVersion *GLVersion::contextVersion = NULL;

GLVersion *GLVersion::getContextVersion() {
    GLint major, minor;

    if (contextVersion == NULL) {
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);

        contextVersion = new GLVersion(major, minor);
    }

    return contextVersion;
}

void GLVersion::printVersion() {
    printf("%i.%i\n",major, minor);
}


GLVersion *GLVersion::versionFromText(char *text) {
    GLint major, minor;

    if ( parseVersion(text, major, minor) ) {
        return new GLVersion(major, minor);
    } else {
        return NULL;
    }
};

GLVersion *GLVersion::versionFromText(std::string text) {
    return versionFromText(text.c_str());
}

GLVersion &GLVersion::operator=(const GLVersion &copy) {
    major = copy.major;
    minor = copy.minor;

    return *this;
}
