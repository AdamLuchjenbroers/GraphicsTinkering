#pragma once

#include "fw1/fw1.h"

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
    virtual void appQuit();

    Shader *vertex, *fragment;
    DisplayInterface *display;

    GLuint program;
    bool running;

    static void valueSwing(GLfloat &offset, GLfloat increment, bool &increase, GLfloat min, GLfloat max);
};
