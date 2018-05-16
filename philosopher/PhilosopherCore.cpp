#include "PhilosopherCore.h"

PhilosopherCore::PhilosopherCore() {
    display = SDLDisplay::resizableDisplay("Dining Philosophers", 400, 400);

    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());
}

void PhilosopherCore::resizeWindow(int newX, int newY) {
    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());

    //GLint proj_loc = program.uniformLocation("projection");
    //glUniformMatrix4fv(proj_loc, 1, false, _projection.buffer());
}

void PhilosopherCore::appInit() {
}

bool PhilosopherCore::appMain() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    display->swapBuffers();
    display->mainLoop(*this);

    return true;
}
