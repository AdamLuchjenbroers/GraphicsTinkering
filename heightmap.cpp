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

    bool buildShaderProgram(const char *vertMain, const char *fragMain);
private:
    GLint _projectionLoc, _xformLoc, _vpsLoc, _lightLoc, _heightLoc;
    Matrix4 _projection, _xform;
    Vector3H _light;
    TextureRef _heightMap;

    int _vertsPerSide, _totalVerts;
    GLfloat _angle;
    GLenum _drawMode;

    void loadUniforms(); 
};

HeightMap::HeightMap(const char *imageFile) {
    display = SDLDisplay::resizableDisplay("Vertex Shader Height Map", 400, 400, false);
    _heightMap = Texture::loadImage(imageFile, GL_TEXTURE0);

    _vertsPerSide = 16;
    _totalVerts = _vertsPerSide * 2 * (_vertsPerSide - 1);
    _angle = 0.0f;
    _drawMode = GL_TRIANGLE_STRIP;
    running = _heightMap.isValid();

}

void HeightMap::resizeWindow(int newX, int newY) {
    _projection = Matrix4::fovHorizontal( 0.2f, 6.0f, 90.0f, display->aspectRatio());

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
        if (_vertsPerSide < 1024) {
            _vertsPerSide *= 2;
            _totalVerts = _vertsPerSide * 2 * (_vertsPerSide - 1);
            glUniform1i(_vpsLoc, _vertsPerSide);
        }
        break;
    case SDLK_z:
        if (_vertsPerSide > 16) {
             _vertsPerSide /= 2;
             _totalVerts = _vertsPerSide * 2 * (_vertsPerSide - 1);
             glUniform1i(_vpsLoc, _vertsPerSide);
        }
        break;
    case SDLK_d:
        _drawMode = GL_TRIANGLE_STRIP;
        running &= buildShaderProgram("heightmap-vertex.sdr", "heightmap-debugfrag.sdr");
        loadUniforms();
        break;
    case SDLK_c:
        _drawMode = GL_TRIANGLE_STRIP;
        running &= buildShaderProgram("heightmap-vertex.sdr", "heightmap-fragment.sdr");
        loadUniforms();
        break;
    case SDLK_p:
        glPointSize(2.0);
        _drawMode = GL_POINTS;
        running &= buildShaderProgram("heightmap-vertex.sdr", "heightmap-pointdebug.sdr");
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

bool HeightMap::buildShaderProgram(const char *mainVert, const char *mainFrag) {
    bool success = true;
    GLuint glerror;

    program.clearProgram();

    success = program.addShader(mainVert, GL_VERTEX_SHADER);
    success &= program.addShader("heightmap-vertfuncs.sdr", GL_VERTEX_SHADER);
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

    return success;
}

void HeightMap::appInit() {
    bool shaderReady = buildShaderProgram("heightmap-vertex.sdr", "heightmap-fragment.sdr");
    //bool shaderReady = buildShaderProgram("heightmap-vertex.sdr", "sb2-fragment.sdr");

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

    glUniformMatrix4fv(_xformLoc, 1, false, _xform.buffer());
    running &= checkGLError("Error encountered enabling loading Transform matrix: %s\n", Logger::LOG_ERROR);

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
        map = std::string("textures/HeightMap.png");
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
