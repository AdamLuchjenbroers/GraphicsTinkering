#include "SDL2/SDL.h" 

int main( int argc, char* args[] ) { 
  SDL_Window *app_window;

  //Start SDL 
  SDL_Init( SDL_INIT_EVERYTHING ); 

  app_window = SDL_CreateWindow("I'm a window", 50,50,200,200, SDL_WINDOW_OPENGL);
  
  SDL_Delay(2000);
 
  SDL_DestroyWindow(app_window);

  //Quit SDL SDL_Quit(); 
   return 0; 
}
