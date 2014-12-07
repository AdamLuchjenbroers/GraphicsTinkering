#include "Matrix4.h"

#include <math.h>

#include <string>

#include <cstring>
#include <cstdio>

Matrix4::Matrix4() {
    int i, j;

    for (j=0;j<4;j++) {
        for(i=0;i<4;i++) {
            if (i == j) {
                at(i,j) = 1.0f;
            } else {
                at(i,j) = 0.0f;
            }
        }
    }
};

Matrix4::Matrix4(GLfloat *buffer) {
    memcpy(_matrix, buffer, sizeof(_matrix));
}

GLfloat &Matrix4::at(int row, int col) {
    return _matrix[(col*4) + row];
};


GLfloat Matrix4::at(int row, int col) const {
    return _matrix[(col*4) + row];
};

bool Matrix4::operator==(const Matrix4 &comp) const {
    return (memcmp(_matrix, comp._matrix, sizeof(_matrix)) == 0);
}

Matrix4 Matrix4::operator*(const Matrix4 &mult) {
    GLfloat newMatrix[16];

    int i,j;
    for (i=0;i<4;i++) {
        for (j=0;j<4;j++) {
            newMatrix[(j*4)+i] = at(i,0) * mult.at(0,j)
                               + at(i,1) * mult.at(1,j)
                               + at(i,2) * mult.at(2,j)
                               + at(i,3) * mult.at(3,j);
        }
    }

    return Matrix4(newMatrix);
}

Vector3H Matrix4::operator*(const Vector3H &mult) {
    GLfloat newVector[4];

    for(int i=0;i<4;i++) {
        newVector[i] = at(i,0) * mult[0]
                     + at(i,1) * mult[1]
                     + at(i,2) * mult[2]
                     + at(i,3) * mult[3];
    }

    return Vector3H(newVector);
}

std::string Matrix4::printable() const {
    char buffer[512];
    const char *format = {
        "\n| %1.4f %1.4f %1.4f %1.4f |"
        "\n| %1.4f %1.4f %1.4f %1.4f |"
        "\n| %1.4f %1.4f %1.4f %1.4f |"
        "\n| %1.4f %1.4f %1.4f %1.4f |\n"
    };

    snprintf(buffer, 512, format
           , _matrix[0], _matrix[4], _matrix[8] , _matrix[12]
           , _matrix[1], _matrix[5], _matrix[9] , _matrix[13]
           , _matrix[2], _matrix[6], _matrix[10], _matrix[14]
           , _matrix[3], _matrix[7], _matrix[11], _matrix[15]
    );

    return std::string(buffer);
};
