/*
 * Spinning cube.
 */

#include "CubeApp.h"

#include <iostream>

class TexturedCube : public CubeApp {
public:
    TexturedCube();

    void appInit();
private:
    TextureRef _cubeTex;
};

TexturedCube::TexturedCube() {
    display = SDLDisplay::resizableDisplay("Textured Spinning Cube", 400, 400);
    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());
}


void TexturedCube::appInit() {
    bool shaderReady = loadVFProgram("texcube-vertex.sdr", "texcube-fragment.sdr");

    if (!shaderReady) {
        exit(1);
    }

    CubeApp::appInit();

    GLint samp_loc = program.uniformLocation("texSampler");
    _cubeTex = Texture::loadImage("textures/rock.bmp", GL_TEXTURE0);
    glUniform1i(samp_loc, 0);
    checkGLError("Error encountered binding Texture Sampler: %s\n", Logger::LOG_ERROR);
}

int main( int argc, char* args[] ) { 
  FrameworkOneApp *thisApp = new TexturedCube();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}
