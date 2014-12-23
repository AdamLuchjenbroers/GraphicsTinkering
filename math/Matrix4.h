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

    /** Returns a pointer to the internal matrix buffer. Intended for
     *  passing the matrix to OpenGL only.
     *  @return A pointer to the matrix data, ready for use by OpenGL
     */
    inline GLfloat* buffer() { return _matrix; }

    /** Create a Matrix describing a translation in 3D space.
     *  @return A matrix describing a translation in 3D space.
     */
    static Matrix4 translate(GLfloat x, GLfloat y, GLfloat z);

    /** Creates a matrix describing a re-scaling along all three axes by 
     *  the scalar k.
     *  @param scaleK The scaling value to use for all three axes.
     *  @return A Matrix describing a scaling in 3D space
     */
    static Matrix4 scale(GLfloat scaleK);

    /** Creates a matrix describing a re-scaling along all three axes by 
     *  the requested vaues
     *  @param scaleX The scaling value to use for the X axis.
     *  @param scaleY The scaling value to use for the Y axis.
     *  @param scaleZ The scaling value to use for the Z axis.
     *  @return A Matrix describing a scaling in 3D space
     */
    static Matrix4 scale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);

    /** Creates a matrix describining a rotation around the x, y and z axes.
        @param rotateX Rotation around the X axis
        @param rotateY Rotation around the Y axis
        @param rotateZ Rotation around the Z axis
        @return A matrix describing the rotation in 3D space
    */
    static Matrix4 rotate(GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ);

    /** Creates a matrix describing a projection frustrum from the origin
        looking along the Z axis.
        @param near Distance to the near clipping plane. 
        @param far Distance to the far clipping plane. 
        @param width The width of the far clipping plane.
        @param height The height of the far clipping plane.
        @return A perspective projection matrix.
    */
    static Matrix4 frustrum(GLfloat near, GLfloat far, GLfloat width, GLfloat height);

    /** Creates a matrix describing a projection frustrum from the origin
        looking along the Z axis.
        @param near Distance to the near clipping plane. 
        @param far Distance to the far clipping plane. 
        @param fov Horizontal field of view.
        @param aspect Aspect ratio.
        @return A perspective projection matrix.
    */
    static Matrix4 fovHorizontal(GLfloat near, GLfloat far, GLfloat fov, GLfloat aspect);

    /** Creates a matrix describing a projection frustrum from the origin
        looking along the Z axis.
        @param near Distance to the near clipping plane. 
        @param far Distance to the far clipping plane. 
        @param fov Vertical field of view.
        @param aspect Aspect ratio.
        @return A perspective projection matrix.
    */
    static Matrix4 fovVertical(GLfloat near, GLfloat far, GLfloat fov, GLfloat aspect);
private:
    GLfloat _matrix[16];

    /** Creates a matrix describing a projection frustrum from the origin
        looking along the Z axis.
        @param near Distance to the near clipping plane. 
        @param far Distance to the far clipping plane. 
        @param h_zoom Horizontal Zoom
        @param v_zoom Vertical Zoom
        @return A perspective projection matrix.
    */
    static Matrix4 zoomProjection(GLfloat near, GLfloat far, GLfloat h_zoom, GLfloat w_zoom);
};

