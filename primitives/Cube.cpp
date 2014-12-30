#include "Cube.h"

#include <cstdlib>
#include <cstring>

using namespace Primitives;

const float Cube::vertexData[] = {
// Pos: X      Y      Z      W|Tex:U     V|Nrml:X      Y      Z     W| Glos
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.1f,
     1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.1f,
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.1f,
     1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.1f,
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.1f,
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.1f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.1f,
    -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.1f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.1f,
    -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.1f,
    -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.1f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.1f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.1f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.1f,
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.1f,
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.1f,
    -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.1f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.1f,
     1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.1f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.1f,
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.1f,
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.1f,
    -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.1f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.1f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
     1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
    -1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
    -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
};

Cube::Cube() {
    _meshBuffer = (GLfloat *) malloc(sizeof(vertexData));
    memcpy(_meshBuffer, vertexData, sizeof(vertexData));
    _triangles = 12;
    _vertices = 36;
}

Cube::Cube(GLfloat scale) {
    _meshBuffer = (GLfloat *) malloc(sizeof(vertexData));
    memcpy(_meshBuffer, vertexData, sizeof(vertexData));
    _triangles = 12;
    _vertices = 36;

    GLfloat *vert = _meshBuffer;
    for (int i = 0; i < _vertices; i++) {
        vert[0] *= scale;
        vert[1] *= scale;
        vert[2] *= scale;

        vert += stride();
    }
}

