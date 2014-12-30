#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>

#include <cstdlib>

class MeshFile {
public:
    virtual ~MeshFile();

    virtual bool hasVertex() { return true; }
    virtual void *offsetVertex() {return 0; };

    virtual bool hasNormal() { return false; };
    virtual void *offsetNormal() = 0;
    virtual bool hasTexUV() { return false; };
    virtual void *offsetTexUV() = 0;

    virtual bool loadBuffer(GLuint vertArray);
    virtual size_t meshDataSize() { return _vertices * stride(); };

    virtual bool mapAttribute(GLuint attribute, int components, void *offset);
    virtual bool mapVertices(GLuint attribute);
    virtual bool mapNormals(GLuint attribute);
    virtual bool mapTexUV(GLuint attribute);

    virtual size_t stride() = 0; 
    virtual unsigned long numVertices() { return _vertices; };
protected:
    GLfloat *_meshBuffer;

    unsigned long _triangles;
    unsigned long _vertices;

    GLuint _glError;
    GLuint _bufferID;

};
