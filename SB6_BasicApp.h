#pragma once

#include "fw1/fw1.h"

class SB6_BasicApp : public EngineApplication {
public:
    ~SB6_BasicApp();

protected:
    void loadShaders(const char *vertexName, const char *fragmentName);
    virtual void appQuit();

    Shader *vertex, *fragment;
    DisplayInterface *display;

    GLuint program;
    bool running;

    static void valueSwing(GLfloat &offset, GLfloat increment, bool &increase, GLfloat min, GLfloat max);
};
