#include "Matrix4.h"
#include "Math.h"

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
    for(int i=0;i<16;i++) {
        GLfloat diff = _matrix[i] - comp._matrix[i];

        if ((diff > FP_MARGIN) || (diff < -FP_MARGIN)) {
            return false;
        } 
    }
    return true;
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
    char buffer[256];
    const char *format = {
          "| %1.4f %1.4f %1.4f %1.4f |"
        "\n| %1.4f %1.4f %1.4f %1.4f |"
        "\n| %1.4f %1.4f %1.4f %1.4f |"
        "\n| %1.4f %1.4f %1.4f %1.4f |"
    };

    snprintf(buffer, 512, format
           , _matrix[0], _matrix[4], _matrix[8] , _matrix[12]
           , _matrix[1], _matrix[5], _matrix[9] , _matrix[13]
           , _matrix[2], _matrix[6], _matrix[10], _matrix[14]
           , _matrix[3], _matrix[7], _matrix[11], _matrix[15]
    );

    return std::string(buffer);
};

Matrix4 Matrix4::translate(GLfloat x, GLfloat y, GLfloat z) {
    GLfloat matData[] = {
            1.0f, 0.0f, 0.0f, 0.0f
          , 0.0f, 1.0f, 0.0f, 0.0f
          , 0.0f, 0.0f, 1.0f, 0.0f
          ,    x,    y,    z, 1.0f
    };

    return Matrix4(matData);
}

Matrix4 Matrix4::scale(GLfloat scaleK) {
    GLfloat matData[] = {
            scaleK,   0.0f,   0.0f, 0.0f
          ,   0.0f, scaleK,   0.0f, 0.0f
          ,   0.0f,   0.0f, scaleK, 0.0f
          ,   0.0f,   0.0f,   0.0f, 1.0f
    };

    return Matrix4(matData);
}

Matrix4 Matrix4::scale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ) {
    GLfloat matData[] = {
            scaleX,   0.0f,   0.0f, 0.0f
          ,   0.0f, scaleY,   0.0f, 0.0f
          ,   0.0f,   0.0f, scaleZ, 0.0f
          ,   0.0f,   0.0f,   0.0f, 1.0f
    };

    return Matrix4(matData);
}

Matrix4 Matrix4::rotate(GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ) {
    GLfloat radianX = (rotateX * M_PI) / 180.0f; 
    GLfloat radianY = (rotateY * M_PI) / 180.0f; 
    GLfloat radianZ = (rotateZ * M_PI) / 180.0f; 

    GLfloat sinX = sin(radianX);
    GLfloat sinY = sin(radianY);
    GLfloat sinZ = sin(radianZ);

    GLfloat cosX = cos(radianX);
    GLfloat cosY = cos(radianY);
    GLfloat cosZ = cos(radianZ);

    GLfloat matData[16];

    // Top row
    matData[0] = cosY * cosZ; 
    matData[4] = (sinX * sinY * cosZ) - (cosX * sinZ); 
    matData[8] = - (sinX * sinZ) - (cosX * sinY * cosZ);
    matData[12] = 0.0f; 

    // Second row
    matData[1] = cosY * sinZ; 
    matData[5] = (cosX * cosZ) + (sinX * sinY * sinZ); 
    matData[9] = (sinX * cosZ) - (cosX * sinY * sinZ);
    matData[13] = 0.0f; 

    // Third row
    matData[2] = sinY; 
    matData[6] = - (sinX * cosY); 
    matData[10] = cosX * cosY;
    matData[14] = 0.0f; 

    // Last row
    matData[3] = 0.0f; 
    matData[7] = 0.0f;
    matData[12] = 0.0f;
    matData[15] = 1.0f; 

    return Matrix4(matData);
}

Matrix4 Matrix4::zoomProjection(GLfloat near, GLfloat far, GLfloat h_zoom, GLfloat w_zoom) {
    GLfloat matData[] = {
            h_zoom,   0.0f,                            0.0f, 0.0f
          ,   0.0f, w_zoom,                            0.0f, 0.0f
          ,   0.0f,   0.0f, (far + near) / (far - near)    , 1.0f
          ,   0.0f,   0.0f, (2 * far * near) / (near - far), 0.0f
    };
    return Matrix4(matData);
}

Matrix4 Matrix4::frustrum(GLfloat near, GLfloat far, GLfloat width, GLfloat height) {
    GLfloat w_zoom = (far * 2.0f) / width; 
    GLfloat h_zoom = (far * 2.0f) / height; 

    return zoomProjection(near, far, h_zoom, w_zoom);
}

Matrix4 Matrix4::fovHorizontal(GLfloat near, GLfloat far, GLfloat fov, GLfloat aspect) {
    GLfloat halfFovRadians = (fov * M_PI) / 360.0f; // Half of the fov angle, represented in radians.

    GLfloat w_zoom = 1.0f / tan(halfFovRadians);
    GLfloat h_zoom = w_zoom / aspect;

    return zoomProjection(near, far, h_zoom, w_zoom);
}

Matrix4 Matrix4::fovVertical(GLfloat near, GLfloat far, GLfloat fov, GLfloat aspect) {
    GLfloat halfFovRadians = (fov * M_PI) / 360.0f; // Half of the fov angle, represented in radians.

    GLfloat h_zoom = 1.0f / tan(halfFovRadians);
    GLfloat w_zoom = w_zoom * aspect;

    return zoomProjection(near, far, h_zoom, w_zoom);
} 
