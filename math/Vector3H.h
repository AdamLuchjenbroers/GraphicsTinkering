#pragma once

#include "Math.h"

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>

#include <string>
#include <cstdio>
#include <cstring>

/** Stores a three dimensional vector as a homogeneous coordinate with four components (including w).
 *  Mathematical operations on this class will typically affect only the x,y and z co-ordinates, with
 *  the w being handled separately.
 */
class Vector3H {
public:
/** Constructs a 0 vector with four components
 */
    Vector3H();
/** Constructs a four component vector using the provided values
 *  @param x The X co-ordinate value
 *  @param y The Y co-ordinate value
 *  @param z The Z co-ordinate value
 *  @param w The W co-ordinate value
 */
    Vector3H(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

/** Constructs a vector by copying an array of four float values
 *  @param source An array of four floating point co-ordinates to initialize the vector with.
 */
    Vector3H(GLfloat *source);

/** The [] operator returns the value of the specified index
 *  @param idx The index to retrieve.
 */
    inline GLfloat &operator[](int idx) {
        // Bounds checking has been left out for performance.
        return _vector[idx];
    };

/** The [] operator returns the value of the specified index
  *  @param idx The index to retrieve.
  */
    inline const GLfloat operator[](int idx) const {
        return _vector[idx];
    }

/** Divides the x, y and z values by a scalar value
 *  @return A Vector with the x,y and z co-ordinates reduced by a scalar value
 */
    inline Vector3H operator/(const GLfloat div) {
        return Vector3H (
                 _vector[0] / div
               , _vector[1] / div
               , _vector[2] / div
               , _vector[3]
                );
    }

/** Divides the x, y and z values by a scalar value
 */
    inline void operator/=(const GLfloat div) {
        _vector[0] /= div;
        _vector[1] /= div;
        _vector[2] /= div;
    }

/** Multiplies the x, y and z values by a scalar value
  * @return A Vector with the x,y and z co-ordinates multiplied by a scalar value
  */
    inline Vector3H operator*(const GLfloat mult) {
        return Vector3H (
                 _vector[0] * mult
               , _vector[1] * mult
               , _vector[2] * mult
               , _vector[3]
                );
    }

/** Multiplies the x, y and z values by a scalar value
  */
    inline void operator*=(const GLfloat mult) {
        _vector[0] *= mult;
        _vector[1] *= mult;
        _vector[2] *= mult;
    }

 /** Compares two vectors, and returns true if both are equal.
  *  @param comp The second vector to compare.
  *  @return True if both vectors match.
  */
    bool operator==(const Vector3H &comp) const;

/** Mem returns the a pointer to the internal buffer of Vector4. This is intended to be used to pass
 *  the vector data to the OpenGL API, and should not be used for any other purpose.
 *  @return A pointer to the internal vector buffer.
 */
    inline GLfloat *mem() {
        return _vector;
    };

/** Calculates and returns the magnitude of this vector, computed based on the x, y and z co-ordinates.
 *  @return The magnitude of this vector.
 */
    GLfloat magnitude();

/** Adjusts this vector to change the magnitude to unit length without changing the direction.
 */
    void normalize();

/** Computes the dot product of two vectors
 *  @param other The other vector to use to compute this dot product
 *  @return The dot product of the vector.
 */
    GLfloat dot(const Vector3H &other);

/** Computes the cross product of two vectors
 *  @param other The other vector to use to compute this cross product
 *  @return The cross product of these vectors.
 */
    Vector3H cross(const Vector3H &other);

/** Produces a printable copy of the vertex data as a string.
 *  @return A printable copy of the vertex data as a string.
 */
    std::string printable() const;
private:
    GLfloat _vector[4];
};
