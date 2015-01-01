#pragma once

#include "fw1/fw1.h"

#define VI_POSITION 0
#define VI_OFFSET 1
#define VI_COLOR 2
#define VI_TEXUV 3
#define VI_NORMAL 4
#define VI_GLOSS 5

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

/** Initialises the shader library, if it has not already been initialised.
  * @return True if the library is / was successfully initialised.
  */
    bool initLibrary(const char *path);

/** Binds attribute locations to their assigned indices. */
    void bindAttributes();

    virtual void appQuit();

    ShaderProgram program;
    SDLDisplay *display;

    bool running;

 /** Updates values to provide an ascending / descending integer sequence
  *  @param value A reference to the value to be updated.
  *  @param increment The value to increase or decrease offset by.
  *  @param increase A reference boolean value, true if value should be increased, false if it should be decreased. Will be updated if value reaches min or max.
  *  @param min The minimum value that value is allowed to reach, increase will be set to true if this value is reached.
  *  @param max The maximum value that value is allowed to reach, increase will be set to false if this value is reached.
  */
    static void valueSwing(GLfloat &value, GLfloat increment, bool &increase, GLfloat min, GLfloat max);

/** Checks for any OpenGL errors, and outputs details to the log if encountered. All errors are logged to the LOG_APPLICATION channel.
 *  @return True if no errors were encountered.
 */
    bool checkGLError(const char *errfmt, Logger::Level errlevel);

};
