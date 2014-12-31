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
    GLint _projectionLoc, _xformLoc, _vpsLoc;
    Matrix4 _projection, _xform;
    TextureRef _heightMap;

    int _vertsPerSide, _totalVerts;
    GLfloat _angle;
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

    Vector3H light = Vector3H(ndcX, ndcY, 1.0, 1.0);
    GLint light_loc = program.uniformLocation("light_pos");
    glUniform4fv(light_loc, 1, light.mem());
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
    }
}
void HeightMap::appInit() {
    bool shaderReady = loadVFProgram("heightmap-vertex.sdr", "heightmap-fragment.sdr");
    //bool shaderReady = loadVFProgram("heightmap-vertex.sdr", "sb2-fragment.sdr");

    if (!shaderReady) {
        exit(1);
    }

    _xformLoc = program.uniformLocation("xform");
    _projectionLoc = program.uniformLocation("projection");

    resizeWindow(400, 400);

    _vpsLoc = program.uniformLocation("vertsPerSide");
    glUniform1i(_vpsLoc, _vertsPerSide);

    GLint uniformLoc = program.uniformLocation("heightMap");
    glUniform1i(uniformLoc, 0);
    running &= checkGLError("Error encountered binding Texture Sampler: %s\n", Logger::LOG_ERROR);

    Vector3H light = Vector3H(0.0f, 0.0f, 1.0f, 1.0f);
    GLint light_loc = program.uniformLocation("light_pos");
    glUniform4fv(light_loc, 1, light.mem());

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

    glUniformMatrix4fv(_xformLoc, 1, false, _xform.buffer());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, _totalVerts);

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
