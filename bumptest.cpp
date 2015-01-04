/* 
 * Generates and renders a heightmap using a vertex shader
 */

#include "fw1/fw1.h"
#include "SB6_BasicApp.h"
#include "math/Matrix4.h"

#define VERTEX_SHADER "bumpcube-vertex.sdr"
#define FRAGMENT_SHADER "bumpcube-fragment.sdr"

#define CORE_PROFILE true

class BumpTest : public SB6_BasicApp {
public:
    BumpTest(const char *imageFile);

    bool appMain();
    void appInit();

    void mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY);
    void resizeWindow(int newX, int newY);
    void keyEvent(SDL_Keysym &key, bool press);

    bool buildShaderProgram(const char *vertMain, const char *fragMain);
private:
    GLint _projectionLoc, _xformLoc, _texLoc, _lightLoc, _specMapLoc, _bumpMapLoc;
    bool _flatten;
    GLuint _vertexArray, _surfaceBuffer;
    Matrix4 _projection, _xform;
    Vector3H _light;
    TextureRef _heightMap;

    GLfloat _angle, _zPlane;
    GLenum _drawMode;

    TextureRef _cubeTex, _specTex, _bumpTex;
    void loadUniforms(); 
};

BumpTest::BumpTest(const char *imageFile) {
    display = SDLDisplay::resizableDisplay("Bump Map Test", 400, 400, CORE_PROFILE);

    _angle = 0.0f;
    _drawMode = GL_TRIANGLE_STRIP;
    running = true; 
    _zPlane = 2.0f;
}

void BumpTest::resizeWindow(int newX, int newY) {
    _projection = Matrix4::fovHorizontal( 0.2f, 6.0f, 90.0f, display->aspectRatio());

    glUniformMatrix4fv(_projectionLoc, 1, false, _projection.buffer());
    running &= checkGLError("Error encountered updating Projection Matrix: %s\n", Logger::LOG_ERROR);
}

void BumpTest::mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY) {
    GLfloat ndcX, ndcY;

    display->toNDC(x, y, ndcX, ndcY);

    _light = Vector3H(ndcX, ndcY, 0.0, 1.0);
    glUniform4fv(_lightLoc, 1, _light.mem());
    checkGLError("Error encountered updating light position: %s\n", Logger::LOG_WARN);
}

void BumpTest::keyEvent(SDL_Keysym &key, bool press) {
    if (!press) {
        return;
    }

    switch(key.sym) {
    case SDLK_d:
        _drawMode = GL_TRIANGLE_STRIP;
        running &= buildShaderProgram(VERTEX_SHADER, "heightmap-debugfrag.sdr");
        loadUniforms();
        break;
    case SDLK_c:
        _drawMode = GL_TRIANGLE_STRIP;
        running &= buildShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER);
        loadUniforms();
        break;
    case SDLK_p:
        glPointSize(2.0);
        _drawMode = GL_POINTS;
        running &= buildShaderProgram(VERTEX_SHADER, "heightmap-pointdebug.sdr");
        loadUniforms();
        break;
    case SDLK_s:
        if (_zPlane < 4.0f) {
            _zPlane += 0.1f;
        }
        break;
    case SDLK_x:
        if (_zPlane > 0.0f) {
            _zPlane -= 0.1f;
        }
        break;
    }
}

const GLfloat surface[] = {
// Position              | UV        | Normal                | Tangent
  1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
  1.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
 -1.0f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
 -1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f
}; 

void BumpTest::loadUniforms() {
    _xformLoc = program.uniformLocation("xform");

    _projectionLoc = program.uniformLocation("projection");
    glUniformMatrix4fv(_projectionLoc, 1, false, _projection.buffer());

    _lightLoc = program.uniformLocation("light_pos");
    glUniform4fv(_lightLoc, 1, _light.mem());

    _texLoc = program.uniformLocation("texSampler");
    glUniform1i(_texLoc, 1);

    _specMapLoc = program.uniformLocation("specSampler");
    glUniform1i(_specMapLoc, 2);

    _bumpMapLoc = program.uniformLocation("bumpSampler");
    glUniform1i(_bumpMapLoc, 3);
}

bool BumpTest::buildShaderProgram(const char *mainVert, const char *mainFrag) {
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
    success &= checkGLError("Error encountered enabling Shader Program\n", Logger::LOG_ERROR);
    return success;
}

void BumpTest::appInit() {
    bool shaderReady = buildShaderProgram(VERTEX_SHADER, FRAGMENT_SHADER);

    if (!shaderReady) {
        exit(1);
    }

    _light = Vector3H(0.0f, 0.0f, 0.0f, 1.0f);
    loadUniforms();

    glGenVertexArrays(1, &_vertexArray);
    glBindVertexArray(_vertexArray);

    glGenBuffers(1, &_surfaceBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _surfaceBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(surface), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(surface), surface);
 
    glVertexAttribPointer(VI_OFFSET, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 14, 0);
    glEnableVertexAttribArray(VI_OFFSET);

    glVertexAttribPointer(VI_TEXUV, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 14, (void *)(sizeof(GLfloat) * 4));
    glEnableVertexAttribArray(VI_TEXUV);

    glVertexAttribPointer(VI_NORMAL, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 14, (void *)(sizeof(GLfloat) * 6));
    glEnableVertexAttribArray(VI_NORMAL);

    glVertexAttribPointer(VI_TANGENT, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 14, (void *)(sizeof(GLfloat) * 10));
    glEnableVertexAttribArray(VI_TANGENT);
 
    _cubeTex = Texture::loadImage("textures/rock.png", GL_TEXTURE1);
    _specTex = Texture::loadImage("textures/grey64.png", GL_TEXTURE2);
    _bumpTex = Texture::loadImage("textures/nrmltest_normal.png", GL_TEXTURE3);

    resizeWindow(400, 400);

    running &= checkGLError("Error encountered binding Texture Sampler: %s\n", Logger::LOG_ERROR);

    glEnable(GL_DEPTH_TEST);
    running &= checkGLError("Error encountered enabling Depth Buffer: %s\n", Logger::LOG_ERROR);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

bool BumpTest::appMain() {
    if (!running) {
        return false;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program.programID());
    running &= checkGLError("Error encountered enabling Shader Program\n", Logger::LOG_ERROR);

    _xform = Matrix4::translate(0.0f, -1.0f, _zPlane) 
           * Matrix4::rotate(40.0f, 0.0f, 0.0f)
           * Matrix4::rotate(0.0f, _angle, 0.0f);

    glUniformMatrix4fv(_xformLoc, 1, false, _xform.buffer());
    running &= checkGLError("Error encountered enabling loading Transform matrix: %s\n", Logger::LOG_ERROR);

    glDrawArrays(_drawMode, 0, 4);
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
        map = std::string("textures/BumpTest2.png");
    } else if (argc == 2) {
        map = std::string(args[1]);
    } else {
        printf("Usage: %s [<Height Map>]\n", args[0]);
        exit(1);
    }

    BumpTest thisApp = BumpTest(map.c_str());

    thisApp.appInit();
    while ( thisApp.appMain() ) {};
 
    return 0;
}
