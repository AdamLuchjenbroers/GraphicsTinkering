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

   success = _shader.addShader("billboard-vertex.sdr", GL_VERTEX_SHADER);   
   success &= _shader.addShader("billboard-fragment.sdr", GL_FRAGMENT_SHADER);   

   if (success == false) {
      Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Failed to build shader program, missing shader\n");

      _running = false;
      return;
   }
}

bool PhilosopherCore::appMain() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    display->swapBuffers();
    display->mainLoop(*this);

    return _running;
}
