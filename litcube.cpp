/*
 * Spinning lit cube.
 */

#include "fw1/SingleLightRig.h"
#include "CubeApp.h"

class LitCube : public CubeApp {
public:
    LitCube();

    void appInit();

    void mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY);

private:
    TextureRef _cubeTex;
    SingleLightRig _lighting;
};

LitCube::LitCube() {
    display = SDLDisplay::resizableDisplay("Lit Spinning Cube", 400, 400);
    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());
}

void LitCube::mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY) {
    GLfloat ndcX, ndcY;

    display->toNDC(x, y, ndcX, ndcY);

    _lighting.setPosition(1, ndcX, ndcY, 1.0);
    _lighting.updateBuffer();
}

void LitCube::appInit() {
    bool shaderReady = true;

    initLibrary("./shader");

    shaderReady &= program.addShader("litcube-vertex.sdr", GL_VERTEX_SHADER);
    shaderReady &= program.addShader("litcube-fragment.sdr", GL_FRAGMENT_SHADER);
    shaderReady &= program.addShader("single-light.sdr", GL_FRAGMENT_SHADER);

    bindAttributes();
    shaderReady &= program.linkProgram();

    glUseProgram(program.programID());

    if (!shaderReady) {
        exit(1);
    }

    CubeApp::appInit();

    _lighting.setBinding(1);
    _lighting.setPosition(1, 0.0f, 0.0f, 1.0f);
    _lighting.setColor(1, 1.0f, 1.0f, 1.0f);
    _lighting.setAmbient(1, 0.2f, 0.2f, 0.2f);
    _lighting.loadRig(program);

    GLint samp_loc = program.uniformLocation("texSampler");
    _cubeTex = Texture::loadImage("textures/crate.png", GL_TEXTURE0);
    glUniform1i(samp_loc, 0);
    checkGLError("Error encountered binding Texture Sampler: %s\n", Logger::LOG_ERROR);

    glEnable(GL_DEPTH_TEST);
    checkGLError("Error encountered enabling Depth Buffer: %s\n", Logger::LOG_ERROR);
}


int main( int argc, char* args[] ) { 
  FrameworkOneApp *thisApp = new LitCube();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}
