#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>

#include <string>
#include <cstdio>

/** Stores a 4x4 Matrix in memory.
 */
class Matrix4 {
public:
    /** Constructs a new 4x4 Identity Matrix
     */
    Matrix4();

    /** Retrieves a reference to the value at the specified column and row.
     *  @param col The 0-based column number.
     *  @param row The 0-based row number.
     *  @return A reference to the value in that row / column.
     */
    GLfloat &at(int col, int row);
    //{
    //    return _matrix[(col*4) + row];
    //};

    /** Produces a printable copy of the matrix data as a string.
     *  @return A printable copy of the matrix data as a string.
     */
    std::string printable() const;
private:
    GLfloat _matrix[16];
};

