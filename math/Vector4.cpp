#include "Vector4.h"

#include <math.h>

Vector4::Vector4() {
    _vector[0] = 0.0f;
    _vector[1] = 0.0f;
    _vector[2] = 0.0f;
    _vector[3] = 0.0f;
};

Vector4::Vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    _vector[0] = x;
    _vector[1] = y;
    _vector[2] = z;
    _vector[3] = w;
};

Vector4::Vector4(GLfloat *source) {
    _vector[0] = source[0];
    _vector[1] = source[1];
    _vector[2] = source[2];
    _vector[3] = source[3];
};

GLfloat Vector4::magnitude() {
    GLfloat pythagoras = 0.0f;

    for(int i = 0; i < 3; i++) {
        pythagoras += _vector[i] * _vector[i];
    }

    return sqrt(pythagoras);
}
