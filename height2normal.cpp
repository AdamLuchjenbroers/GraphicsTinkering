/* 
 * Generates and renders a heightmap using a vertex shader
 */

#include "fw1/fw1.h"
#include "SB6_BasicApp.h"
#include "math/Matrix4.h"

#define VERTEX_SHADER "height2normal-vertex.sdr"
#define FRAGMENT_SHADER "height2normal-fragment.sdr"

#define CORE_PROFILE true

class HeightMap : public SB6_BasicApp {
public:
    HeightMap(const char *imageFile);

    bool appMain();
    void appInit();

    void keyEvent(SDL_Keysym &key, bool press);

    bool buildShaderProgram(const char *vertMain, const char *fragMain);
private:
    GLint _projectionLoc, _xformLoc, _vpsLoc, _lightLoc, _heightLoc, _flattenLoc;
    bool _flatten;
    GLuint _vertexArray;
    Matrix4 _projection, _xform;
    Vector3H _light;
    TextureRef _heightMap;

    int _vertsPerSide, _totalVerts;
    GLfloat _angle, _zPlane;
    GLenum _drawMode;

    void loadUniforms(); 
};

HeightMap::HeightMap(const char *imageFile) {
    display = SDLDisplay::resizableDisplay("HeightMap -> NormalMap", 512, 512, CORE_PROFILE);
    _heightMap = Texture::loadImage(imageFile, GL_TEXTURE1);

    _vertsPerSide = 16;
    _totalVerts = _vertsPerSide * 2 * (_vertsPerSide - 1);
    _angle = 0.0f;
    _drawMode = GL_TRIANGLE_STRIP;
    running = _heightMap.isValid();
    _flatten = false;
    _zPlane = 2.0f;
}

void HeightMap::keyEvent(SDL_Keysym &key, bool press) {
    if (!press) {
        return;
    }

    switch(key.sym) {
    case SDLK_a:
        if (_vertsPerSide < 1024) {
            _vertsPerSide *= 2;
            _totalVerts = _vertsPerSide * 2 * (_vertsPerSide - 1);
            glUniform1i(_vpsLoc, _vertsPerSide);
            checkGLError("Error encountered updating Vertices Per Side count: %s\n", Logger::LOG_WARN);
        }
        break;
    case SDLK_z:
        if (_vertsPerSide > 4) {
             _vertsPerSide /= 2;
             _totalVerts = _vertsPerSide * 2 * (_vertsPerSide - 1);
             glUniform1i(_vpsLoc, _vertsPerSide);
             checkGLError("Error encountered updating Vertices Per Side count: %s\n", Logger::LOG_WARN);
        }
        break;
    }
}

void HeightMap::loadUniforms() {
    _xformLoc = program.uniformLocation("xform");

    _vpsLoc = program.uniformLocation("vertsPerSide");
    glUniform1i(_vpsLoc, _vertsPerSide);

    _heightLoc = program.uniformLocation("heightMap");
    glUniform1i(_heightLoc, 1);
}

bool HeightMap::buildShaderProgram(const char *mainVert, const char *mainFrag) {
    bool success = true;
    GLuint glerror;

    program.clearProgram();

    success = program.addShader(mainVert, GL_VERTEX_SHADER);
    success &= program.addShader("heightmap-vertfuncs.sdr", GL_VERTEX_SHADER);
    success &= program.addShader(mainFrag, GL_FRAGMENT_SHADER);

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

void HeightMap::appInit() {
    bool shaderReady = buildShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER);

    if (!shaderReady) {
        exit(1);
    }

    _light = Vector3H(0.0f, 0.0f, 0.0f, 1.0f);
    loadUniforms();

    glGenVertexArrays(1, &_vertexArray);
    glBindVertexArray(_vertexArray);

    resizeWindow(512, 512);

    running &= checkGLError("Error encountered binding Texture Sampler: %s\n", Logger::LOG_ERROR);

    glEnable(GL_DEPTH_TEST);
    running &= checkGLError("Error encountered enabling Depth Buffer: %s\n", Logger::LOG_ERROR);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

bool HeightMap::appMain() {
    if (!running) {
        return false;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program.programID());
    running &= checkGLError("Error encountered enabling Shader Program\n", Logger::LOG_ERROR);

    glDrawArrays(_drawMode, 0, _totalVerts);
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
    std::string map; 

    if (argc == 1) {
        map = std::string("textures/HeightMap2.png");
    } else if (argc == 2) {
        map = std::string(args[1]);
    } else {
        printf("Usage: %s [<Height Map>]\n", args[0]);
        exit(1);
    }

    HeightMap thisApp = HeightMap(map.c_str());

    thisApp.appInit();
    while ( thisApp.appMain() ) {};
 
    return 0;
}
