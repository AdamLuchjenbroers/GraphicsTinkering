#include "PhilosopherCore.h"

PhilosopherCore::PhilosopherCore() {
    display = SDLDisplay::resizableDisplay("Dining Philosophers", 400, 400);

    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());

    _running = true;
}

void PhilosopherCore::resizeWindow(int newX, int newY) {
    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());

    GLint proj_loc = _shader.uniformLocation("projection");
    glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());
}

void PhilosopherCore::appInit() {
   GLuint glerror;
   bool success = true;

   if (!ShaderLibrary::isReady()) {
       ShaderLibrary::setLibraryPath("./shader"); 
   }

   success = _shader.addShader("philosopher.sdr", GL_VERTEX_SHADER);   
   success &= _shader.addShader("radboard-geo.sdr", GL_GEOMETRY_SHADER);   
   success &= _shader.addShader("billboard-fragment.sdr", GL_FRAGMENT_SHADER);   

   if (success == false) {
      Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Failed to build shader program, missing shader\n");

      _running = false;
      return;
   }

    success = _shader.linkProgram();

    if (success == false) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Unable to link rendering program: %s\n", gluErrorString(glerror));

        _running = false;
       return;
    }
    
    glUseProgram(_shader.programID());

    glGenVertexArrays(1, &_vertexarray);
    glBindVertexArray(_vertexarray);

    _angle = 0.0f;
}

bool PhilosopherCore::appMain() {

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glVertexAttrib1f(0, _angle);
    _angle += 0.1f;

    glDrawArrays(GL_POINTS, 0, 5);

    display->swapBuffers();
    display->mainLoop(*this);

    return _running;
}
