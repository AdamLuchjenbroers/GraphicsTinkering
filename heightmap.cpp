/* 
 * Generates and renders a heightmap using a vertex shader
 */

#include "fw1/fw1.h"
#include "SB6_BasicApp.h"
#include "math/Matrix4.h"


class HeightMap : public SB6_BasicApp {
public:
    HeightMap(const char *imageFile);

    bool appMain();
    void appInit();

    void mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY);
    void resizeWindow(int newX, int newY);
    void keyEvent(SDL_Keysym &key, bool press);
private:
    GLint _projectionLoc, _xformLoc, _vpsLoc, _lightLoc, _heightLoc;
    Matrix4 _projection, _xform;
    Vector3H _light;
    TextureRef _heightMap;

    int _vertsPerSide, _totalVerts;
    GLfloat _angle;

    void loadUniforms(); 
};

HeightMap::HeightMap(const char *imageFile) {
    display = SDLDisplay::resizableDisplay("Vertex Shader Height Map", 400, 400);
    _heightMap = Texture::loadImage(imageFile, GL_TEXTURE0);

    _vertsPerSide = 16;
    _totalVerts = _vertsPerSide * 2 * (_vertsPerSide - 1);
    _angle = 0.0f;
    running = _heightMap.isValid();

}

void HeightMap::resizeWindow(int newX, int newY) {
    _projection = Matrix4::fovHorizontal( 0.1f, 6.0f, 90.0f, display->aspectRatio());

    glUniformMatrix4fv(_projectionLoc, 1, false, _projection.buffer());
    running &= checkGLError("Error encountered updating Projection Matrix: %s\n", Logger::LOG_ERROR);
}

void HeightMap::mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY) {
    GLfloat ndcX, ndcY;

    display->toNDC(x, y, ndcX, ndcY);

    _light = Vector3H(ndcX, ndcY, 1.0, 1.0);
    glUniform4fv(_lightLoc, 1, _light.mem());
    checkGLError("Error encountered updating light position: %s\n", Logger::LOG_WARN);
}

void HeightMap::keyEvent(SDL_Keysym &key, bool press) {
    if (!press) {
        return;
    }

    switch(key.sym) {
    case SDLK_a:
        _vertsPerSide += 16;
        _totalVerts = _vertsPerSide * 2 * (_vertsPerSide - 1);
        glUniform1i(_vpsLoc, _vertsPerSide);
        break;
    case SDLK_z:
        if (_vertsPerSide > 16) {
             _vertsPerSide -= 16;
             _totalVerts = _vertsPerSide * 2 * (_vertsPerSide - 1);
             glUniform1i(_vpsLoc, _vertsPerSide);
        }
        break;
    case SDLK_d:
        program.clearProgram();
        running &= loadVFProgram("heightmap-vertex.sdr", "heightmap-debugfrag.sdr");
        loadUniforms();
        break;
    case SDLK_c:
        program.clearProgram();
        running &= loadVFProgram("heightmap-vertex.sdr", "heightmap-fragment.sdr");
        loadUniforms();
        break;
    }
}

void HeightMap::loadUniforms() {
    _xformLoc = program.uniformLocation("xform");

    _projectionLoc = program.uniformLocation("projection");
    glUniformMatrix4fv(_projectionLoc, 1, false, _projection.buffer());

    _vpsLoc = program.uniformLocation("vertsPerSide");
    glUniform1i(_vpsLoc, _vertsPerSide);

    _heightLoc = program.uniformLocation("heightMap");
    glUniform1i(_heightLoc, 0);

    _lightLoc = program.uniformLocation("light_pos");
    glUniform4fv(_lightLoc, 1, _light.mem());
}

void HeightMap::appInit() {
    bool shaderReady = loadVFProgram("heightmap-vertex.sdr", "heightmap-fragment.sdr");
    //bool shaderReady = loadVFProgram("heightmap-vertex.sdr", "sb2-fragment.sdr");

    if (!shaderReady) {
        exit(1);
    }

    _light = Vector3H(0.0f, 0.0f, 0.0f, 1.0f);
    loadUniforms();

    resizeWindow(400, 400);

    running &= checkGLError("Error encountered binding Texture Sampler: %s\n", Logger::LOG_ERROR);

    glEnable(GL_DEPTH_TEST);
    running &= checkGLError("Error encountered enabling Depth Buffer: %s\n", Logger::LOG_ERROR);
}

bool HeightMap::appMain() {
    if (!running) {
        return false;
    }
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _xform = Matrix4::translate(0.0f, -1.0f, 2.0f) 
           * Matrix4::rotate(40.0f, 0.0f, 0.0f)
           * Matrix4::rotate(0.0f, _angle, 0.0f);

    if (_xformLoc >= 0) {
        glUniformMatrix4fv(_xformLoc, 1, false, _xform.buffer());
        running &= checkGLError("Error encountered enabling loading Transform matrix: %s\n", Logger::LOG_ERROR);
    }

    glDrawArrays(GL_TRIANGLE_STRIP, 0, _totalVerts);
    running &= checkGLError("Error encountered calling glDrawArrays: %s\n", Logger::LOG_ERROR);

    display->swapBuffers();
    display->mainLoop(*this);

    _angle += 0.5f;
    if (_angle >= 360.0f) {
        _angle -= 360.0f;
    };

    return true;
}

int main( int argc, char* args[] ) { 
    char *defaultMap = "textures/HeightMap.png";
    char *map;

    if (argc == 1) {
        map = defaultMap;
    } else if (argc == 2) {
        map = args[1];
    } else {
        printf("Usage: %s [<Height Map>]\n", args[0]);
        exit(1);
    }

    HeightMap thisApp = HeightMap(map);

    thisApp.appInit();
    while ( thisApp.appMain() ) {};
 
    return 0;
}
