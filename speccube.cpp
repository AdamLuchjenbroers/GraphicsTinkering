/* 
 * Renders a spinning cube with specular highlights using
 * a second texture as a specular map. 
 */

#include "CubeApp.h"

#define VERTEX_SHADER "litcube-vertex.sdr"
#define FRAGMENT_SHADER "speccube-fragment.sdr"

class SpecularCube : public CubeApp {
public:
    SpecularCube();

    void appInit();

    void mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY);
    void keyEvent(SDL_Keysym &key, bool press);

    bool buildSpecCubeProgram(const char *vertMain, const char *fragMain);
private:
    GLint _texLoc, _specMapLoc;
    GLenum _drawMode;

    TextureRef _cubeTex;
    TextureRef _specTex;
    SingleLightRig _lighting;

    void loadUniforms(); 
};

SpecularCube::SpecularCube() {
    display = SDLDisplay::resizableDisplay("Specular Mapped Spinning Cube", 400, 400, true);

    _drawMode = GL_TRIANGLES;
}

void SpecularCube::keyEvent(SDL_Keysym &key, bool press) {
    if (!press) {
        return;
    }

    switch(key.sym) {
    case SDLK_d:
        _drawMode = GL_TRIANGLES;
        running &= buildSpecCubeProgram(VERTEX_SHADER, "litdebug-fragment.sdr");
        loadUniforms();
        break;
    case SDLK_c:
        _drawMode = GL_TRIANGLES;
        running &= buildSpecCubeProgram(VERTEX_SHADER, FRAGMENT_SHADER);
        loadUniforms();
        break;
    case SDLK_p:
        glPointSize(2.0);
        _drawMode = GL_POINTS;
        running &= buildSpecCubeProgram(VERTEX_SHADER, "heightmap-pointdebug.sdr");
        loadUniforms();
        break;
    }
}

void SpecularCube::mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY) {
    GLfloat ndcX, ndcY;

    display->toNDC(x, y, ndcX, ndcY);

    _lighting.setPosition(1, ndcX, ndcY, 1.0);
    _lighting.updateBuffer();
}

void SpecularCube::loadUniforms() {
    _texLoc = program.uniformLocation("texSampler");
    glUniform1i(_texLoc, 1);

    _specMapLoc = program.uniformLocation("specSampler");
    glUniform1i(_specMapLoc, 2);
}

bool SpecularCube::buildSpecCubeProgram(const char *mainVert, const char *mainFrag) {
    bool success = true;
    GLuint glerror;

    program.clearProgram();

    success = program.addShader(mainVert, GL_VERTEX_SHADER);
    success &= program.addShader(mainFrag, GL_FRAGMENT_SHADER);
    success &= program.addShader("single-light.sdr", GL_FRAGMENT_SHADER);

    if (success == false) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Failed to build shader program, missing shader\n");

        return false;
    }

    bindAttributes();

    success = program.linkProgram();

    if (success == false) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Unable to link rendering program: %s\n", gluErrorString(glerror));

        return false;
    }
    
    glUseProgram(program.programID());
    success &= checkGLError("Error encountered enabling Shader Program\n", Logger::LOG_ERROR);
    return success;
}

void SpecularCube::appInit() {
    bool shaderReady = buildSpecCubeProgram(VERTEX_SHADER, FRAGMENT_SHADER);

    if (!shaderReady) {
        exit(1);
    }

    CubeApp::appInit();
 
    _cubeTex = Texture::loadImage("textures/crate.png", GL_TEXTURE1);
    _specTex = Texture::loadImage("textures/crate_specular.png", GL_TEXTURE2);
    running &= checkGLError("Error encountered binding Texture Sampler: %s\n", Logger::LOG_ERROR);

    _lighting.setBinding(1);
    _lighting.setPosition(1, 0.0f, 0.0f, 1.0f);
    _lighting.setColor(1, 1.0f, 1.0f, 1.0f);
    _lighting.setAmbient(1, 0.2f, 0.2f, 0.2f);
    _lighting.loadRig(program);

    loadUniforms();

    resizeWindow(400, 400);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

int main( int argc, char* args[] ) {
    std::string map; 

    SpecularCube thisApp = SpecularCube();

    thisApp.appInit();
    while ( thisApp.appMain() ) {};
 
    return 0;
}
