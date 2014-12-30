/*
 * Spinning cube.
 */

#include "fw1/fw1.h"
#include "SB6_BasicApp.h"
#include "math/Matrix4.h"
#include "primitives/Cube.h"

#include <iostream>

#define COLOUR_RED 0
#define COLOUR_GREEN 1
#define COLOUR_BLUE 2
#define COLOUR_ALPHA 3


class TexturedCube : public SB6_BasicApp {
public:
    TexturedCube();

    bool appMain();
    void appInit();

    void resizeWindow(int newX, int newY);

private:
    GLuint vertexarray, vertexbuffer, colourbuffer;

    Matrix4 _projection;

    TextureRef _cubeTex;
    Primitives::Cube _cube;

    GLfloat angle;
};

TexturedCube::TexturedCube() {
    display = SDLDisplay::resizableDisplay("Textured Spinning Cube", 400, 400);
    running = true;

    angle = 0.0f;   

    vertexarray = 0;

    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());
}

void TexturedCube::resizeWindow(int newX, int newY) {
    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());

    GLint proj_loc = program.uniformLocation("projection");
    glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());
}

void TexturedCube::appInit() {
    bool shaderReady = loadVFProgram("texcube-vertex.sdr", "texcube-fragment.sdr");

    if (!shaderReady) {
        exit(1);
    }

    glGenVertexArrays(1, &vertexarray);
    _cube.loadBuffer(vertexarray);
    _cube.mapVertices(VI_OFFSET);
    _cube.mapNormals(VI_NORMAL);
    _cube.mapTexUV(VI_TEXUV);
    _cube.mapAttribute(VI_GLOSS, 1, (void *)(sizeof(GLfloat) * 10)); 

    GLint proj_loc = program.uniformLocation("projection");
    glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());

    GLint samp_loc = program.uniformLocation("texSampler");
    _cubeTex = Texture::loadImage("textures/rock.bmp", GL_TEXTURE0);
    glUniform1i(samp_loc, 0);
    checkGLError("Error encountered binding Texture Sampler: %s\n", Logger::LOG_ERROR);

    glEnable(GL_DEPTH_TEST);
    checkGLError("Error encountered enabling Depth Buffer: %s\n", Logger::LOG_ERROR);
}

bool TexturedCube::appMain() {
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
    glDrawArrays(GL_TRIANGLES, 0, 36);

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
  FrameworkOneApp *thisApp = new TexturedCube();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}
