#include "SDL2/SDL.h" 
#include "GL/gl.h"

int main( int argc, char* args[] ) { 
  SDL_Window *app_window;
  GLfloat color[] = {0.0f, 0.0f, 1.0f, 1.0f};

  //Start SDL 
  SDL_Init( SDL_INIT_EVERYTHING ); 

  app_window = SDL_CreateWindow("I'm a window", 50,50,200,200, SDL_WINDOW_OPENGL);
  
  glClear(GL_COLOR_BUFFER_BIT);

  SDL_Delay(2000);
 
  SDL_DestroyWindow(app_window);

  //Quit SDL SDL_Quit(); 
   return 0; 
}
