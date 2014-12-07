#include "Vector3H.h"

#include <math.h>

Vector3H::Vector3H() {
    _vector[0] = 0.0f;
    _vector[1] = 0.0f;
    _vector[2] = 0.0f;
    _vector[3] = 0.0f;
};

Vector3H::Vector3H(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    _vector[0] = x;
    _vector[1] = y;
    _vector[2] = z;
    _vector[3] = w;
};

Vector3H::Vector3H(GLfloat *source) {
    _vector[0] = source[0];
    _vector[1] = source[1];
    _vector[2] = source[2];
    _vector[3] = source[3];
};

GLfloat Vector3H::magnitude() {
    GLfloat pythagoras = 0.0f;

    for(int i = 0; i < 3; i++) {
        pythagoras += _vector[i] * _vector[i];
    }

    return sqrt(pythagoras);
}

void Vector3H::normalize() {
    *this /= this->magnitude();
}

GLfloat Vector3H::dot(const Vector3H &other) {
    return (_vector[0] * other._vector[0] )
         + (_vector[1] * other._vector[1] )
         + (_vector[2] * other._vector[2] );
}

Vector3H Vector3H::cross(const Vector3H &other) {
    return Vector3H(
        (_vector[1] * other._vector[2]) - (_vector[2] * other._vector[1])
      , (_vector[2] * other._vector[0]) - (_vector[0] * other._vector[2])
      , (_vector[0] * other._vector[1]) - (_vector[1] * other._vector[0])
      , _vector[4] //Don't change w.
    );
}

std::string Vector3H::printable() const {
    char buffer[32];
    const char *format = "[%1.4f %1.4f %1.4f %1.4f]";

    snprintf(buffer, 512, format
           , _vector[0], _vector[1], _vector[2] , _vector[3]
    );

    return std::string(buffer);
}
