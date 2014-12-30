#pragma once

#include "../fw1/MeshFile.h"
#include "../math/Vector3H.h"

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>

struct PyramidVert;

namespace Primitives {

class Pyramid: public MeshFile {
public:
    Pyramid();
    Pyramid(GLfloat scale);
    Pyramid(int sides);
    Pyramid(GLfloat scale, int sides);

    bool hasVertex() { return true; };
    void *offsetVertex() { return 0; };

    bool hasNormal() { return true; };
    void *offsetNormal();

    bool hasTexUV() { return true; };
    void *offsetTexUV();

    size_t stride();
private:
    bool generatePyramid(GLfloat scale, int sides);

    Vector3H pointAt(int point, GLfloat radius, GLfloat z);

    int _sides;
};

};
