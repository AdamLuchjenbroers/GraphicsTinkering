
#include <stdio.h>
#include "SDL2/SDL.h" 
#include "GL/gl.h"

int main( int argc, char* args[] ) { 
  SDL_Window *app_window;
  SDL_GLContext app_glcontext;

  //Start SDL 
  SDL_Init( SDL_INIT_EVERYTHING ); 

  app_window = SDL_CreateWindow("I'm a window", 50,50,200,200, SDL_WINDOW_OPENGL);
  app_glcontext = SDL_GL_CreateContext(app_window);  
  SDL_GL_MakeCurrent(app_window, app_glcontext);

  printf("GL Version: %s\n",  glGetString(GL_VERSION));
  printf("GL Renderer: %s\n", glGetString(GL_RENDERER));
  printf("GL Vendor: %s\n", glGetString(GL_VENDOR));

  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(app_window);

  SDL_Delay(2000);
 
  SDL_DestroyWindow(app_window);

  //Quit SDL SDL_Quit(); 
   return 0; 
}
