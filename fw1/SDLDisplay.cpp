#include "SDLDisplay.h"

#include "Logger.h"

SDLDisplay::SDLDisplay() {
    _width = 200;
    _height = 200;
    
    _offsetX = 50;
    _offsetY = 50;

    _sdlFlags = SDL_WINDOW_OPENGL;

    app_window = NULL;

    strncpy(_title, "Untitled Window", 64);
}
 
SDLDisplay::~SDLDisplay() {
    this->close();
}

SDLDisplay *SDLDisplay::basicDisplay(const char *title, int width, int height) {
    SDLDisplay *newDisplay = new SDLDisplay();

    newDisplay->_width = width;
    newDisplay->_height = height;

    strncpy(newDisplay->_title, title, 64);

    newDisplay->createWindow(true);
    newDisplay->logRendererInfo();
    
    return newDisplay;
}

SDLDisplay *SDLDisplay::resizableDisplay(const char *title, int width, int height, bool coreProfile) {
    SDLDisplay *newDisplay = new SDLDisplay();

    newDisplay->_width = width;
    newDisplay->_height = height;

    strncpy(newDisplay->_title, title, 64);

    newDisplay->setResizable(true);

    newDisplay->createWindow(coreProfile);
    newDisplay->logRendererInfo();
    
    return newDisplay;
}

SDLDisplay *SDLDisplay::resizableDisplay(const char *title, int width, int height) {
    return resizableDisplay(title, width, height, true);    
}

bool SDLDisplay::createWindow(bool coreProfile) {
    if ( SDL_WasInit(SDL_INIT_VIDEO) == 0 ) {
	SDL_Init( SDL_INIT_VIDEO );
    } 

    app_window = SDL_CreateWindow(_title, _offsetX, _offsetY, _width, _height, _sdlFlags);
    if (coreProfile) {
        //Use OpenGL 3.x core 
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 ); 
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    }
    app_glcontext = SDL_GL_CreateContext(this->app_window);

    SDL_GL_MakeCurrent(this->app_window, this->app_glcontext);
}

void SDLDisplay::swapBuffers() {
    SDL_GL_SwapWindow(this->app_window);
}

void SDLDisplay::close() {
    SDL_DestroyWindow(this->app_window);
}

void SDLDisplay::setResizable(bool resize) {
    if (resize) {
        _sdlFlags |= SDL_WINDOW_RESIZABLE;
    } else {
        _sdlFlags &= ~SDL_WINDOW_RESIZABLE;
    }
}

bool SDLDisplay::isResizable() {
    Uint32 windowFlags;

    if (app_window != NULL) {
        windowFlags = SDL_GetWindowFlags(app_window);        
    } else {
        windowFlags = _sdlFlags;
    }

    return ((windowFlags & SDL_WINDOW_RESIZABLE) != 0);
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
        
        switch(event.type) {
        case SDL_KEYDOWN:
            app.keyEvent( event.key.keysym, true);
            break;
        case SDL_KEYUP:
            app.keyEvent( event.key.keysym, false);
            break;
        case SDL_MOUSEMOTION:
            app.mouseMovementEvent(event.motion.state, event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
            break; 
        case SDL_WINDOWEVENT:
            processWindowEvent(event.window, app);
            break;
        case SDL_QUIT:
            app.appQuit();
            break;
        }
   }
}

void SDLDisplay::processWindowEvent(SDL_WindowEvent &winEvent, FrameworkOneApp &app) {
    switch (winEvent.event) {
        case SDL_WINDOWEVENT_RESIZED:
            _width = winEvent.data1;
            _height = winEvent.data2;
            glViewport(0,0,_width, _height);
            app.resizeWindow(_width, _height);
            break;
        case SDL_WINDOWEVENT_MOVED:
            _offsetX = winEvent.data1;
            _offsetY = winEvent.data2;
            break;
	      case SDL_WINDOWEVENT_CLOSE:
            app.appQuit();
            break;
        //TODO: These events currently aren't processed
	case SDL_WINDOWEVENT_SHOWN:
	case SDL_WINDOWEVENT_HIDDEN:
	case SDL_WINDOWEVENT_EXPOSED:
	case SDL_WINDOWEVENT_SIZE_CHANGED:
	case SDL_WINDOWEVENT_MINIMIZED:
	case SDL_WINDOWEVENT_MAXIMIZED:
	case SDL_WINDOWEVENT_ENTER:
	case SDL_WINDOWEVENT_LEAVE:
	case SDL_WINDOWEVENT_FOCUS_GAINED:
	case SDL_WINDOWEVENT_FOCUS_LOST: 
            break;
    }
}
