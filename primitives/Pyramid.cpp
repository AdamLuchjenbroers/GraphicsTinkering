#include "Pyramid.h"

#include <cstdlib>
#include <math.h>

using namespace Primitives;

struct PyramidVert {
    GLfloat position[4];
    GLfloat normal[4];
    GLfloat texUV[2];
};

Pyramid::Pyramid() {
    _meshBuffer = NULL;
    generatePyramid(1.0f, 3);
}

Pyramid::Pyramid(int sides) {
    _meshBuffer = NULL;
    generatePyramid(1.0f, sides);
}

Pyramid::Pyramid(GLfloat scale) {
    _meshBuffer = NULL;
    generatePyramid(scale, 3);
}

Pyramid::Pyramid(GLfloat scale, int sides) {
    _meshBuffer = NULL;
    generatePyramid(scale, sides);
}

void *Pyramid::offsetNormal() { return (void *) offsetof(struct PyramidVert, normal); }
void *Pyramid::offsetTexUV() { return (void *) offsetof(struct PyramidVert, texUV); }
size_t Pyramid::stride() { return sizeof(struct PyramidVert); };

bool Pyramid::generatePyramid(GLfloat scale, int sides) {
    PyramidVert *vertexData, *currentVertex; 
    _triangles = (sides * 2) - 2;
    _vertices = _triangles * 3;
    _sides = sides;

    vertexData = (PyramidVert *) malloc(_vertices * stride());
    currentVertex = vertexData;

    GLfloat topZ = scale;
    GLfloat botZ = topZ * cos(M_PI * 2.0f / 3.0f);
    GLfloat radius = scale / sin(M_PI * 2.0f / 3.0f);

    Vector3H top = Vector3H(0.0f, 0.0f, topZ, 1.0f);

    for (int face = 0; face < sides; face++) {
         Vector3H left = pointAt(face, radius, botZ);
         Vector3H right = pointAt((face + 1) % sides, radius, botZ);

         Vector3H planeL = left - top;
         Vector3H planeR = right - top;
  
         Vector3H normal = planeR.cross(planeL);
         normal[3] = 0.0f;
         normal.normalize();

         top.writeTo(currentVertex->position);
         normal.writeTo(currentVertex->normal);
         currentVertex->texUV[0] = 0.5f;
         currentVertex->texUV[1] = 1.0f;
         currentVertex++;

         right.writeTo(currentVertex->position);
         normal.writeTo(currentVertex->normal);
         currentVertex->texUV[0] = (1.0f / sides) * (face + 1);
         currentVertex->texUV[1] = 0.0f;
         currentVertex++;

         left.writeTo(currentVertex->position);
         normal.writeTo(currentVertex->normal);
         currentVertex->texUV[0] = (1.0f / sides) * face;
         currentVertex->texUV[1] = 0.0f;
         currentVertex++;
    } 

    //Stitch the bottom
    Vector3H botNormal = Vector3H(0.0f, 0.0f, -1.0f, 0.0f);
    Vector3H stitchHub = pointAt(0, radius, botZ);
    for (int stitch = 2; stitch < sides; stitch++) {
        Vector3H stitchLeft = pointAt(stitch-1, radius, botZ);
        Vector3H stitchRight = pointAt(stitch, radius, botZ);

        stitchHub.writeTo(currentVertex->position);
        botNormal.writeTo(currentVertex->normal);
        currentVertex->texUV[0] = stitchHub[0];
        currentVertex->texUV[1] = stitchHub[1];
	currentVertex++;

	stitchRight.writeTo(currentVertex->position);
	botNormal.writeTo(currentVertex->normal);
	currentVertex->texUV[0] = stitchRight[0];
	currentVertex->texUV[1] = stitchRight[1];
        currentVertex++;

        stitchLeft.writeTo(currentVertex->position);
        botNormal.writeTo(currentVertex->normal);
        currentVertex->texUV[0] = stitchLeft[0];
        currentVertex->texUV[1] = stitchLeft[1];
	currentVertex++;
    }

    if (_meshBuffer != NULL) {
        free(_meshBuffer);
    }
    _meshBuffer = (GLfloat *) vertexData;
}

Vector3H Pyramid::pointAt(int face, GLfloat radius, GLfloat z) {
    GLfloat angle = ((2 * M_PI) / _sides) * face;

    return Vector3H(sin(angle) * radius, cos(angle) * radius, z, 1.0f); 
}
