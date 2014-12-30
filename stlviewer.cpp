/*
 * Spinning cube.
 */

#include "fw1/fw1.h"
#include "SB6_BasicApp.h"
#include "math/Matrix4.h"

#include <iostream>

#define COLOUR_RED 0
#define COLOUR_GREEN 1
#define COLOUR_BLUE 2
#define COLOUR_ALPHA 3


class STLViewer : public SB6_BasicApp {
public:
    STLViewer();

    bool appMain();
    void appInit();

    void resizeWindow(int newX, int newY);

    void mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY);

private:
    GLuint vertexarray, vertexbuffer, colourbuffer;

    Matrix4 _projection;

    STLMesh _meshData;

    GLfloat angle;
};

STLViewer::STLViewer() {
    display = SDLDisplay::resizableDisplay("STL Model Viewer", 400, 400);
    running = true;

    angle = 0.0f;   

    vertexarray = 0;

    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());
}

void STLViewer::resizeWindow(int newX, int newY) {
    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());

    GLint proj_loc = program.uniformLocation("projection");
    glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());
}

void STLViewer::mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY) {
    GLfloat ndcX, ndcY;

    display->toNDC(x, y, ndcX, ndcY);

    Vector3H light = Vector3H(ndcX, ndcY, 1.0, 1.0);
    GLint light_loc = program.uniformLocation("light_pos");
    glUniform4fv(light_loc, 1, light.mem());
}

const size_t vi_record = sizeof(GLfloat) * 11;  
const void *uvOffset = (void *) (sizeof(GLfloat) * 4);
const void *normalOffset = (void *) (sizeof(GLfloat) * 6);
const void *glossOffset = (void *) (sizeof(GLfloat) * 10);

void STLViewer::appInit() {
    bool shaderReady = loadVFProgram("litcube-vertex.sdr", "stlviewer-fragment.sdr");

    if (!shaderReady) {
        exit(1);
    }

    _meshData.loadSTL("/home/notavi/Dropbox/Viral backer (+)/3D models/Cyborg Colossus ver2.stl");

    glGenVertexArrays(1, &vertexarray);
    _meshData.loadBuffer(vertexarray);
    _meshData.mapVertices(VI_OFFSET);
    _meshData.mapNormals(VI_NORMAL);

    GLint proj_loc = program.uniformLocation("projection");
    glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());

    GLint light_loc = program.uniformLocation("light_pos");
    Vector3H light  = Vector3H(1.0f, 0.0f, 0.0f, 1.0f);
    glUniform4fv(light_loc, 1, light.mem());

    glEnable(GL_DEPTH_TEST);
    checkGLError("Error encountered enabling Depth Buffer: %s\n", Logger::LOG_ERROR);
}

bool STLViewer::appMain() {
    GLenum glerror;
    GLint offsetLocation;
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLint xform_loc = program.uniformLocation("xform");
    Matrix4 translate = Matrix4::translate(0.0f, 0.0f, 4.0f);
    Matrix4 rotate = Matrix4::rotate(angle / 2.0f, angle, 0.0f); 

    Matrix4 xform = translate * rotate;

    glUniformMatrix4fv(xform_loc, 1, false, xform.buffer());
  
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
  FrameworkOneApp *thisApp = new STLViewer();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}
