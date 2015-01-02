/* 
 * Generates and renders a heightmap using a vertex shader
 */

#include "fw1/fw1.h"
#include "SB6_BasicApp.h"
#include "math/Matrix4.h"
#include "primitives/Cube.h"

#define VERTEX_SHADER "litcube-vertex.sdr"
#define FRAGMENT_SHADER "speccube-fragment.sdr"

class SpecularCube : public SB6_BasicApp {
public:
    SpecularCube();

    bool appMain();
    void appInit();

    void mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY);
    void resizeWindow(int newX, int newY);
    void keyEvent(SDL_Keysym &key, bool press);

    bool buildShaderProgram(const char *vertMain, const char *fragMain);
private:
    GLint _projectionLoc, _xformLoc, _texLoc, _lightLoc, _specMapLoc;
    GLuint _vertexArray;
    GLenum _drawMode;

    GLfloat _angle;
    Matrix4 _projection, _xform;
    Vector3H _light;

    TextureRef _cubeTex;
    TextureRef _specTex;
    Primitives::Cube _cube;


    void loadUniforms(); 
};

SpecularCube::SpecularCube() {
    display = SDLDisplay::resizableDisplay("Specular Mapped Spinning Cube", 400, 400, true);

    _angle = 0.0f;
    _drawMode = GL_TRIANGLES;

}

void SpecularCube::resizeWindow(int newX, int newY) {
    _projection = Matrix4::fovHorizontal( 0.2f, 6.0f, 90.0f, display->aspectRatio());

    glUniformMatrix4fv(_projectionLoc, 1, false, _projection.buffer());
    running &= checkGLError("Error encountered updating Projection Matrix: %s\n", Logger::LOG_ERROR);
}

void SpecularCube::mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY) {
    GLfloat ndcX, ndcY;

    display->toNDC(x, y, ndcX, ndcY);

    _light = Vector3H(ndcX, ndcY, 1.0, 1.0);
    glUniform4fv(_lightLoc, 1, _light.mem());
    checkGLError("Error encountered updating light position: %s\n", Logger::LOG_WARN);
}

void SpecularCube::keyEvent(SDL_Keysym &key, bool press) {
    if (!press) {
        return;
    }

    switch(key.sym) {
    case SDLK_d:
        _drawMode = GL_TRIANGLES;
        running &= buildShaderProgram(VERTEX_SHADER, "litdebug-fragment.sdr");
        loadUniforms();
        break;
    case SDLK_c:
        _drawMode = GL_TRIANGLES;
        running &= buildShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER);
        loadUniforms();
        break;
    case SDLK_p:
        glPointSize(2.0);
        _drawMode = GL_POINTS;
        running &= buildShaderProgram(VERTEX_SHADER, "heightmap-pointdebug.sdr");
        loadUniforms();
        break;
    }
}

void SpecularCube::loadUniforms() {
    _xformLoc = program.uniformLocation("xform");

    _projectionLoc = program.uniformLocation("projection");
    glUniformMatrix4fv(_projectionLoc, 1, false, _projection.buffer());

    _lightLoc = program.uniformLocation("light_pos");
    glUniform4fv(_lightLoc, 1, _light.mem());

    _texLoc = program.uniformLocation("texSampler");
    glUniform1i(_texLoc, 1);

    _specMapLoc = program.uniformLocation("specSampler");
    glUniform1i(_specMapLoc, 2);
}

bool SpecularCube::buildShaderProgram(const char *mainVert, const char *mainFrag) {
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
    bool shaderReady = buildShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER);

    if (!shaderReady) {
        exit(1);
    }

    glGenVertexArrays(1, &_vertexArray);
    _cube.loadBuffer(_vertexArray);
    _cube.mapVertices(VI_OFFSET);
    _cube.mapNormals(VI_NORMAL);
    _cube.mapTexUV(VI_TEXUV);
    _cube.mapAttribute(VI_GLOSS, 1, (void *)(sizeof(GLfloat) * 10));
 
    _cubeTex = Texture::loadImage("textures/crate.png", GL_TEXTURE1);
    _specTex = Texture::loadImage("textures/crate_specular.png", GL_TEXTURE2);

    _light = Vector3H(0.0f, 0.0f, 0.0f, 1.0f);
    loadUniforms();

    resizeWindow(400, 400);

    running &= checkGLError("Error encountered binding Texture Sampler: %s\n", Logger::LOG_ERROR);

    glEnable(GL_DEPTH_TEST);
    running &= checkGLError("Error encountered enabling Depth Buffer: %s\n", Logger::LOG_ERROR);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

bool SpecularCube::appMain() {
    if (!running) {
        return false;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program.programID());
    running &= checkGLError("Error encountered enabling Shader Program\n", Logger::LOG_ERROR);

    _xform = Matrix4::translate(0.0f, 0.0f, 3.0f) 
           * Matrix4::rotate(_angle / 2.0, _angle, 0.0f);

    glUniformMatrix4fv(_xformLoc, 1, false, _xform.buffer());
    running &= checkGLError("Error encountered enabling loading Transform matrix: %s\n", Logger::LOG_ERROR);

    glDrawArrays(_drawMode, 0, _cube.numVertices());
    running &= checkGLError("Error encountered calling glDrawArrays: %s\n", Logger::LOG_ERROR);

    display->swapBuffers();
    display->mainLoop(*this);

    _angle += 0.5f;
    if (_angle >= 720.0f) {
        _angle -= 720.0f;
    };

    return true;
}

int main( int argc, char* args[] ) {
    std::string map; 

    SpecularCube thisApp = SpecularCube();

    thisApp.appInit();
    while ( thisApp.appMain() ) {};
 
    return 0;
}
