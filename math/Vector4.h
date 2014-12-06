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
private:
    GLfloat _vector[4];
};
