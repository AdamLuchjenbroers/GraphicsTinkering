#pragma once

#include "LightRig.h"

struct LightInfo {
    GLfloat position[4];
    GLfloat color[4];
    GLfloat ambient[4];
};

class SingleLightRig : public LightRig {
public:
    SingleLightRig();
    int lightsSupported() { return 1; }

    bool setPosition(int light, Vector3H pos);
    bool setPosition(int light, GLfloat x, GLfloat y, GLfloat z);

    bool setColor(int light, GLfloat r, GLfloat g, GLfloat b);
    bool setAmbient(int light, GLfloat r, GLfloat g, GLfloat b);

    bool loadRig(ShaderProgram &program);
    bool updateBuffer();
private:
    void writeValues(GLfloat *buffer, GLfloat v1, GLfloat v2, GLfloat v3);

    GLuint _rigBuffer;

    LightInfo _light;
};
