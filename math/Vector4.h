#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>

class Vector4 {
public:
/** Constructs a 0 vector with four components
 */
    Vector4();
/** Constructs a four component vector using the provided values
 *  @param x The X co-ordinate value
 *  @param y The Y co-ordinate value
 *  @param z The Z co-ordinate value
 *  @param w The W co-ordinate value
 */
    Vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

/** Constructs a vector by copying an array of four float values
 *  @param source An array of four floating point co-ordinates to initialize the vector with.
 */
    Vector4(GLfloat *source);

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

private:
    GLfloat _vector[4];
};
