/*
 * Spinning cube.
 */

#include "fw1/fw1.h"
#include "SB6_BasicApp.h"
#include "math/Matrix4.h"
#include "primitives/Pyramid.h"

#include <iostream>

#define COLOUR_RED 0
#define COLOUR_GREEN 1
#define COLOUR_BLUE 2
#define COLOUR_ALPHA 3


class Pyramid : public SB6_BasicApp {
public:
    Pyramid(GLfloat scale, int sides);

    bool appMain();
    void appInit();

    void resizeWindow(int newX, int newY);

    void mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY);
    void keyEvent(SDL_Keysym &key, bool press);
private:
    GLuint vertexarray, vertexbuffer, colourbuffer;

    Matrix4 _projection, _scale;

    Primitives::Pyramid _meshData;

    GLfloat angle, _scaleVal;
};

Pyramid::Pyramid(GLfloat scale, int sides) {
    display = SDLDisplay::resizableDisplay("Pyramid", 400, 400);

    running = true;

    angle = 0.0f;   

    vertexarray = 0;

    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());
}

void Pyramid::resizeWindow(int newX, int newY) {
    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());

    GLint proj_loc = program.uniformLocation("projection");
    glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());
}

void Pyramid::mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY) {
    GLfloat ndcX, ndcY;

    display->toNDC(x, y, ndcX, ndcY);

    Vector3H light = Vector3H(ndcX, ndcY, 1.0, 1.0);
    GLint light_loc = program.uniformLocation("light_pos");
    glUniform4fv(light_loc, 1, light.mem());
}

void Pyramid::keyEvent(SDL_Keysym &key, bool press) {
    if ((key.sym == SDLK_KP_MINUS || key.sym == SDLK_MINUS) && (_scaleVal > 1.0f)) {
        _scaleVal -= 0.2f;
    }

    if ((key.sym == SDLK_KP_PLUS || key.sym == SDLK_PLUS) && (_scaleVal < 10.0f)) {
        _scaleVal += 0.2f;
    }

    _scale = Matrix4::scale(_scaleVal);
    Matrix4 translate = Matrix4::translate(0.0f, 0.0f, 4.0f);
    Matrix4 xform = translate * _scale;

    GLint xform_loc = program.uniformLocation("xform");
    glUniformMatrix4fv(xform_loc, 1, false, xform.buffer());
}

void Pyramid::appInit() {
    bool shaderReady = loadVFProgram("fakesphere-vertex.sdr", "fakesphere-fragment.sdr");

    if (!shaderReady) {
        exit(1);
    }

    glGenVertexArrays(1, &vertexarray);
    _meshData.loadBuffer(vertexarray);
    _meshData.mapVertices(VI_OFFSET);
    // HACK: Use the vertex position as if it were a normal
    _meshData.mapVertices(VI_NORMAL);

    _scaleVal = 1.0f;
    _scale = Matrix4::scale(_scaleVal);
    Matrix4 translate = Matrix4::translate(0.0f, 0.0f, 4.0f);
    Matrix4 xform = translate * _scale;

    GLint xform_loc = program.uniformLocation("xform");
    glUniformMatrix4fv(xform_loc, 1, false, xform.buffer());

    GLint proj_loc = program.uniformLocation("projection");
    glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());

    GLint light_loc = program.uniformLocation("light_pos");
    Vector3H light  = Vector3H(1.0f, 0.0f, 0.0f, 1.0f);
    glUniform4fv(light_loc, 1, light.mem());

    glEnable(GL_DEPTH_TEST);
    running &= checkGLError("Error encountered enabling Depth Buffer: %s\n", Logger::LOG_ERROR);
}

bool Pyramid::appMain() {
    GLenum glerror;
    GLint offsetLocation;
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Matrix4 rotate = Matrix4::rotate(angle / 2.0f, angle, 0.0f); 

    GLint rotate_loc = program.uniformLocation("rotate");
    glUniformMatrix4fv(rotate_loc, 1, false, rotate.buffer());
  
    checkGLError("Error encountered while calling glVertexAttrib4fv: %s\n", Logger::LOG_ERROR);
    glDrawArrays(GL_TRIANGLES, 0, _meshData.numVertices());

    checkGLError("Error encountered while calling glDrawArrays: %s\n", Logger::LOG_ERROR);
    display->swapBuffers();

    display->mainLoop(*this);

    SDL_Delay(10);

    angle += 0.5f;
    if (angle >= 720.0f) {
        angle -= 720.0f;
    }

    return running;
}


int main( int argc, char* args[] ) {
 
  Pyramid thisApp = Pyramid(1.0f, 3);

  thisApp.appInit();

  while (thisApp.appMain()) { };
 
  return 0;
}
