#pragma once

#include "MeshFile.h"

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>

class STLMesh : public MeshFile {
public:
    STLMesh();
    STLMesh(const char *filename);

    bool loadSTL(const char *filename);

    bool hasNormals() { return true; }

    size_t stride() { return sizeof(GLfloat) * 8; };
    void *offsetVertex() { return 0; };
    void *offsetNormal() { return (void *) (sizeof(GLfloat) * 4); };
    void *offsetTexUV()  { return 0; };
private:
};
