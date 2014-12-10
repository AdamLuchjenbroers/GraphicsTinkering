#pragma once

#include "fw1.h"

#include <map>

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
/** Link the selected shaders together to create a shader program.
 *  @return True if the link process was successful.
 */
    bool linkProgram();

/** Retrieves the OpenGL object ID for the compiled shader program. Returns -1
 *  if the shader program has not been successfully linked.
 *  @return The OpenGL object ID for the compiled shader program or -1 of the shader
 *  program has not been linked.
 */
    GLuint programID();
private:
    GLuint _program;
    bool _linked;

    std::map<GLenum, ShaderRef> _shaders;
};
