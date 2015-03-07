#pragma once

#include "SB6_BasicApp.h"
#include "math/Matrix4.h"
#include "primitives/Cube.h"

/** Framework app for loading and rendering a spinning cube.
  * It provides some abstractions to avoid repeated code
  */
class CubeApp : public SB6_BasicApp {
public:
    CubeApp();

    bool appMain();
    void appInit();

    void resizeWindow(int newX, int newY);
protected:
    GLuint vertexarray; 

    Matrix4 _projection;
    Primitives::Cube _cube;

    GLfloat angle;
};
