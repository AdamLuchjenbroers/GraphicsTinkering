#include "Matrix4.h"

#include <math.h>

#include <string>
#include <cstdio>

Matrix4::Matrix4() {
    int i, j;

    printf("\n");

    for (i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            if (i == j) {
                at(i,j) = 1.0f;
            } else {
                at(i,j) = 0.0f;
            }
        }
    }
};

GLfloat &Matrix4::at(int col, int row) {
    return _matrix[(col*4) + row];
};

std::string Matrix4::printable() const {
    char buffer[512];
    char *format = {
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
