#pragma once

#include "fw1/fw1.h"

#include <map>

class SB6_BasicApp : public FrameworkOneApp {
public:
    ~SB6_BasicApp();

protected:
/** Creates and loads a simple shader program consisting of a Vertex and Fragment Shader
 *  @param vertexName The name of the vertex shader to be loaded.
 *  @param fragmentName The name of the fragment shader to be loaded.
 *  @return True if all shader components loaded successfully
 */
    bool loadVFProgram(const char *vertexName, const char *fragmentName);

/** Add a shader to the shader program.
 *  @param shaderName The name of the shader script file.
 *  @param shaderType The pipeline stage this shader corresponds to.
 *  @return True if the shader was successfully found and added.
 */
    bool loadShader(const char *shaderName, const GLenum shaderType);

/** Links the compiled shaders into a new
 *  @return True if the program was successfully created.
 */
    bool linkProgram();

    virtual void appQuit();

    ShaderProgram program;
    DisplayInterface *display;

    bool running;

    static void valueSwing(GLfloat &offset, GLfloat increment, bool &increase, GLfloat min, GLfloat max);

};
