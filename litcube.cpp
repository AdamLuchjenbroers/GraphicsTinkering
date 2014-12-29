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


class BasicCube : public SB6_BasicApp {
public:
    BasicCube();

    bool appMain();
    void appInit();

    void resizeWindow(int newX, int newY);

    void mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY);

private:
    GLuint vertexarray, vertexbuffer, colourbuffer;

    Matrix4 _projection;

    TextureRef _cubeTex;

    GLfloat angle;
};

BasicCube::BasicCube() {
    display = SDLDisplay::resizableDisplay("Textured Spinning Cube", 400, 400);
    running = true;

    angle = 0.0f;   

    vertexarray = 0;

    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());
}

void BasicCube::resizeWindow(int newX, int newY) {
    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());

    GLint proj_loc = program.uniformLocation("projection");
    glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());
}

void BasicCube::mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY) {
    GLfloat ndcX, ndcY;

    display->toNDC(x, y, ndcX, ndcY);

    Vector3H light = Vector3H(ndcX, ndcY, 1.0, 1.0);
    GLint light_loc = program.uniformLocation("light_pos");
    glUniform4fv(light_loc, 1, light.mem());
}

static const float vertices[] =
{
// Pos: X      Y      Z      W|Tex:U     V|Nrml:X      Y      Z     W| Glos
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.1f,
     1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.1f,
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.1f,
     1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.1f,
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.1f,
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.1f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.1f,
    -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.1f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.1f,
    -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.1f,
    -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.1f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.1f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.1f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.1f,
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.1f,
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.1f,
    -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.1f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.1f,
     1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.1f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.1f,
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.1f,
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.1f,
    -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.1f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.1f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
     1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
    -1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
    -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.1f,
};

const size_t vi_record = sizeof(GLfloat) * 11;  
const void *uvOffset = (void *) (sizeof(GLfloat) * 4);
const void *normalOffset = (void *) (sizeof(GLfloat) * 6);
const void *glossOffset = (void *) (sizeof(GLfloat) * 10);

void BasicCube::appInit() {
    bool shaderReady = loadVFProgram("litcube-vertex.sdr", "litcube-fragment.sdr");

    if (!shaderReady) {
        exit(1);
    }

    glGenVertexArrays(1, &vertexarray);
    glBindVertexArray(vertexarray);
    checkGLError("Error encountered creating Vertex Array: %s\n", Logger::LOG_ERROR);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    checkGLError("Error encountered creating Vertex Array Buffer: %s\n", Logger::LOG_ERROR);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    checkGLError("Error encountered loading Vertex Array Buffer: %s\n", Logger::LOG_ERROR);

    glVertexAttribPointer(VI_OFFSET, 4, GL_FLOAT, GL_FALSE, vi_record, 0);
    glEnableVertexAttribArray(VI_OFFSET);
    checkGLError("Error encountered preparing Position Vertex Data: %s\n", Logger::LOG_ERROR);

    glVertexAttribPointer(VI_TEXUV, 2, GL_FLOAT, GL_FALSE, vi_record, uvOffset);
    glEnableVertexAttribArray(VI_TEXUV);
    checkGLError("Error encountered preparing Texture UV Vertex Data: %s\n", Logger::LOG_ERROR);

    glVertexAttribPointer(VI_NORMAL, 4, GL_FLOAT, GL_FALSE, vi_record, normalOffset);
    glEnableVertexAttribArray(VI_NORMAL);
    checkGLError("Error encountered preparing Vertex Normal Data: %s\n", Logger::LOG_ERROR);

    glVertexAttribPointer(VI_GLOSS, 1, GL_FLOAT, GL_FALSE, vi_record, glossOffset);
    glEnableVertexAttribArray(VI_GLOSS);
    checkGLError("Error encountered preparing Surface Gloss Data: %s\n", Logger::LOG_ERROR);

    GLint proj_loc = program.uniformLocation("projection");
    glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());

    GLint samp_loc = program.uniformLocation("texSampler");
    _cubeTex = Texture::loadImage("textures/rock.bmp");
    _cubeTex.activate(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glUniform1i(samp_loc, 0);
    checkGLError("Error encountered binding Texture Sampler: %s\n", Logger::LOG_ERROR);

    GLint light_loc = program.uniformLocation("light_pos");
    Vector3H light  = Vector3H(1.0f, 0.0f, 0.0f, 1.0f);
    glUniform4fv(light_loc, 1, light.mem());

    glEnable(GL_DEPTH_TEST);
    checkGLError("Error encountered enabling Depth Buffer: %s\n", Logger::LOG_ERROR);
}

bool BasicCube::appMain() {
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
  FrameworkOneApp *thisApp = new BasicCube();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}
