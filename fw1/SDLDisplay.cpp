#include "SDLDisplay.h"

#include "Logger.h"

SDLDisplay::SDLDisplay() {
    _width = 200;
    _height = 200;
    
    _offsetX = 50;
    _offsetY = 50;

    strncpy(_title, "Untitled Window", 64);
}
 
SDLDisplay::~SDLDisplay() {
    this->close();
}

SDLDisplay *SDLDisplay::basicDisplay(const char *title, int width, int height) {
    SDLDisplay *newDisplay = new SDLDisplay();

    newDisplay->_width = width;
    newDisplay->_height = height;

    newDisplay->_offsetX = 50;
    newDisplay->_offsetY = 50;

    strncpy(newDisplay->_title, title, 64);

    newDisplay->createWindow();
    newDisplay->logRendererInfo();
    
    return newDisplay;
}

bool SDLDisplay::createWindow() {
    SDL_Init( SDL_INIT_EVERYTHING ); 

    app_window = SDL_CreateWindow(_title, _offsetX, _offsetY, _width, _height, SDL_WINDOW_OPENGL);
    app_glcontext = SDL_GL_CreateContext(this->app_window);

    SDL_GL_MakeCurrent(this->app_window, this->app_glcontext);
}

void SDLDisplay::swapBuffers() {
    SDL_GL_SwapWindow(this->app_window);
}

void SDLDisplay::close() {
    SDL_DestroyWindow(this->app_window);
}

std::string SDLDisplay::printable() {
    char buffer[512];

    snprintf(buffer, 512, "GL Version: %s\nGL Renderer: %s\nGL Vendor: %s\nGLSL Version: %s\n"
            , glGetString(GL_VERSION), glGetString(GL_RENDERER), glGetString(GL_VENDOR)
            , glGetString(GL_SHADING_LANGUAGE_VERSION));

    return std::string(buffer);
}

void SDLDisplay::logRendererInfo() {
    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_APPLICATION, "%s", printable().c_str());
}

void SDLDisplay::mainLoop(FrameworkOneApp &app) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            app.appQuit();
        };

        if (event.type == SDL_KEYDOWN) {
            app.keyEvent( event.key.keysym, true);
        };

        if (event.type == SDL_KEYUP) {
            app.keyEvent( event.key.keysym, true);
        };
    }
}
