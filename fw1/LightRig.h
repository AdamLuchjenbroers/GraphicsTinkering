#pragma once

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>

#include "ShaderProgram.h"
#include "../math/Vector3H.h"

/** Virtual class for managing lighting data */
class LightRig {
public:
    virtual int lightsSupported() = 0;

    virtual bool setPosition(int light, Vector3H pos) = 0;
    virtual bool setPosition(int light, GLfloat x, GLfloat y, GLfloat z) = 0;
    virtual bool setColor(int light, GLfloat r, GLfloat g, GLfloat b) = 0;
    virtual bool setAmbient(int light, GLfloat r, GLfloat g, GLfloat b) = 0;

    virtual bool setBinding(GLuint bindPoint);
    virtual bool loadRig(ShaderProgram &program) = 0;
protected:
    GLuint _binding;
};

