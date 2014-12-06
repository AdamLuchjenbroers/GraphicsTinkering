#pragma once

#include "fw1/fw1.h"

#include <map>

class SB6_BasicApp : public EngineApplication {
public:
    ~SB6_BasicApp();

protected:
/** Creates and loads a simple shader program consisting of a Vertex and Fragment Shader
 *  @param vertexName The name of the vertex shader to be loaded.
 *  @param fragmentName The name of the fragment shader to be loaded.
 *  @return True if all shader components loaded successfully
 */
    bool loadVFProgram(const char *vertexName, const char *fragmentName);


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
