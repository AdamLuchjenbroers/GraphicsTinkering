#include "CubeApp.h"
#include "fw1/Logger.h"


CubeApp::CubeApp() {
    running = true;

    _angle = 0.0f;   
    _speed = 0.2f;

    vertexarray = 0;
}

void CubeApp::resizeWindow(int newX, int newY) {
    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());

    GLint proj_loc = program.uniformLocation("projection");
    glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());
}

void CubeApp::appInit() {
    glGenVertexArrays(1, &vertexarray);
    _cube.loadBuffer(vertexarray);
    _cube.mapVertices(VI_OFFSET);
    _cube.mapNormals(VI_NORMAL);
    _cube.mapTangents(VI_TANGENT);
    _cube.mapTexUV(VI_TEXUV);
    _cube.mapAttribute(VI_GLOSS, 1, (void *)(sizeof(GLfloat) * 10)); 

    GLint proj_loc = program.uniformLocation("projection");
    glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());

    glEnable(GL_DEPTH_TEST);
    checkGLError("Error encountered enabling Depth Buffer: %s\n", Logger::LOG_ERROR);
}

bool CubeApp::appMain() {
    GLenum glerror;
    GLint offsetLocation;
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLint xform_loc = program.uniformLocation("xform");
    Matrix4 translate = Matrix4::translate(0.0f, 0.0f, 4.0f);
    Matrix4 rotate = Matrix4::rotate(_angle / 2.0f, _angle, 0.0f); 

    Matrix4 xform = translate * rotate;

    glUniformMatrix4fv(xform_loc, 1, false, xform.buffer());
  
    checkGLError("Error encountered while calling glVertexAttrib4fv: %s\n", Logger::LOG_ERROR);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    checkGLError("Error encountered while calling glDrawArrays: %s\n", Logger::LOG_ERROR);
    display->swapBuffers();

    display->mainLoop(*this);

    SDL_Delay(10);

    _angle += _speed;
    if (_angle >= 720.0f) {
        _angle -= 720.0f;
    }

    return running;
}
