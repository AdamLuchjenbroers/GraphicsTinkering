#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>

#include "Vector3H.h"

#include <string>
#include <cstdio>

/** Stores a 4x4 Matrix in memory.
 */
class Matrix4 {
public:
    /** Constructs a new 4x4 Identity Matrix
     */
    Matrix4();

    /** Constructs a new 4x4 Matrix by copying from the buffer provided.
     *  The provided matrix is expected to be in the form of a single array
     *  of 16 floating point numbers in column-major order.
     */
    Matrix4(GLfloat *buffer);

    /** Retrieves a reference to the value at the specified column and row.
     *  @param col The 0-based column number.
     *  @param row The 0-based row number.
     *  @return A reference to the value in that row / column.
     */
    GLfloat &at(int row, int col);
    GLfloat at(int row, int col) const;
    //{
    //    return _matrix[(col*4) + row];
    //};

    /** Compares two matrices, and returns true if both are equal.
     *  @param comp The second matrix to compare.
     *  @return True if both matrices match.
     */
    bool operator==(const Matrix4 &mult) const;

    /** Multiply two matrices together to the product of both matrices.
     *  @param mult The other matrix to multiply this by
     *  @result The product of both matrices.
     */
    Matrix4 operator*(const Matrix4 &mult);

    /** Multiply a matrix with a vector (treating the vector as a column vector)
     *  together to produce a transformed vector
     *  @param mult The vector to multiply this Matrix by
     *  @result The product of the vector and matrix.
     */
    Vector3H operator*(const Vector3H &vec);


    /** Produces a printable copy of the matrix data as a string.
     *  @return A printable copy of the matrix data as a string.
     */
    std::string printable() const;
private:
    GLfloat _matrix[16];
};

