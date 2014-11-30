#define GL_GLEXT_PROTOTYPES
#include "GL/glcorearb.h"

class VersionNumber {
public:
    virtual bool operator<(const VersionNumber &right);
    virtual bool operator>(const VersionNumber &right);
    virtual bool operator<=(const VersionNumber &right);
    virtual bool operator>=(const VersionNumber &right);

    virtual bool operator==(const VersionNumber &right);
protected:
    GLint major, minor;
};

class GLVersion : public VersionNumber {
public:
    GLVersion(GLint major, GLint minor);
    GLVersion();

    void printVersion();

    static GLVersion *versionFromText(char *text);
};
