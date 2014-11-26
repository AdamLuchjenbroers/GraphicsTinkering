#include "sdldisplay.h"

SDLDisplay::SDLDisplay(const char *title, int width, int height) {
  //Start SDL 
  SDL_Init( SDL_INIT_EVERYTHING ); 

  this->app_window = SDL_CreateWindow(title, 50,50,width,height, SDL_WINDOW_OPENGL);
  this->app_glcontext = SDL_GL_CreateContext(this->app_window);  
  SDL_GL_MakeCurrent(this->app_window, this->app_glcontext);

  printf("GL Version: %s\n",  glGetString(GL_VERSION));
  printf("GL Renderer: %s\n", glGetString(GL_RENDERER));
  printf("GL Vendor: %s\n", glGetString(GL_VENDOR));
}
 
SDLDisplay::~SDLDisplay() {
  this->close();
}

void SDLDisplay::swapBuffers() {
  SDL_GL_SwapWindow(this->app_window);
}

void SDLDisplay::close() {
  SDL_DestroyWindow(this->app_window);
}

void SDLDisplay::mainLoop(EngineApplication &app) {
  SDL_Event event;


  while(SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      app.appQuit();
    };
 }
}