#include "SDLDisplay.h"

#include "Logger.h"

SDLDisplay::SDLDisplay(const char *title, int w, int h) {
    //Start SDL 
    SDL_Init( SDL_INIT_EVERYTHING ); 

    width = w;
    height = h;

    this->app_window = SDL_CreateWindow(title, 50,50,width,height, SDL_WINDOW_OPENGL);
    this->app_glcontext = SDL_GL_CreateContext(this->app_window);

    //Request a core profile, as some implementations (i.e. Mesa) only expose OpenGL 3.0
    //when supporting compatibility profiles  
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_MakeCurrent(this->app_window, this->app_glcontext);

    logRendererInfo();
}
 
SDLDisplay::~SDLDisplay() {
    this->close();
}

SDLDisplay *SDLDisplay::basicDisplay(const char *title, int width, int height) {
    return new SDLDisplay(title, width, height);
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
