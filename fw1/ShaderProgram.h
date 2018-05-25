#pragma once

#include "ShaderRef.h"

#include <list>

/** Constructs a shader program from a selected set of shader objects.
 */
class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();

/** Add a shader to the shader program.
 *  @param name The name of the shader script file.
 *  @param type The pipeline stage this shader corresponds to.
 *  @return True if the shader was successfully found and added.
 */
    bool addShader(const char *name, const GLenum type );

/** Binds an attribute to a specific input location
 *  @param attrib Attribute name
 *  @param location Intended attribute location
 */
    void bindAttribute(const GLchar *attrib, GLuint location);
/** Unlink the currently loaded shader program to allow it to be re-linked.
 */
    void clearProgram();
/** Link the selected shaders together to create a shader program.
 *  @return True if the link process was successful.
 */
    bool linkProgram();
/** Returns the location index of the specified Uniform parameter
 *  @param uniform The name of the uniform being queried.
 *  @return The location index of the specified Uniform parameter
 */
    GLint uniformLocation(const GLchar *uniform);

/** Returns true if this shader program is linked and ready for use.
 *  @return True if this shader program has been properly linked.
 */
    bool isLinked();

/** Returns the location index of the specified Uniform block
 *  @param uniform The name of the uniform block being queried.
 *  @return The location index of the specified Uniform block
 */
    GLint uniformBlockLocation(const GLchar *uniform);

/** Returns the location index of the specified Attribute input.
 *  @param uniform The name of the shader attribute being queried.
 *  @return The location index of the specified Attribute
 */
    GLint attributeLocation(const GLchar *name);

/** Retrieves the OpenGL object ID for the compiled shader program. Returns -1
 *  if the shader program has not been successfully linked.
 *  @return The OpenGL object ID for the compiled shader program or -1 of the shader
 *  program has not been linked.
 */
    GLuint programID();
private:
    GLuint _program;
    bool _linked;

    std::list<ShaderRef> _shaders;
};
