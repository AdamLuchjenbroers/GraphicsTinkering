#pragma once

#include "../fw1/MeshFile.h"

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>

namespace Primitives {

class Cube: public MeshFile {
public:
    Cube();
    Cube(GLfloat scale);

    bool hasVertex() { return true; };
    void *offsetVertex() {return 0; };

    bool hasNormal() { return true; };
    void *offsetNormal() { return (void *)(sizeof(GLfloat) * 6); };

    bool hasTexUV() { return true; };
    void *offsetTexUV() { return (void *)(sizeof(GLfloat) * 4); };

    bool hasTangent() { return true; };
    void *offsetTangent() { return (void *)(sizeof(GLfloat) * 11); };

    size_t stride() { return sizeof(GLfloat) * 15; };
private:
    static const float vertexData[];
};

};
