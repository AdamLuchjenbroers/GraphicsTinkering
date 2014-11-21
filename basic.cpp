
#include <stdio.h>
#include "SDL2/SDL.h" 
#include "GL/gl.h"

#define COLOUR_RED 0
#define COLOUR_GREEN 1
#define COLOUR_BLUE 2
#define COLOUR_ALPHA 3

void draw_colour(GLfloat r, GLfloat g, GLfloat b) {
    printf("R:%f G:%f B:%f\n",r,g,b);

    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

GLfloat *colour_for_time(int time) {
    static GLfloat colour[4];

    if ( time >= 256 ) {
      colour[COLOUR_RED] = (512 - time) / 256.0f; 
    } else {
      colour[COLOUR_RED] = time / 256.0f; 
    };

    if ( time >= 256 ) {
      colour[COLOUR_GREEN] = (time - 256) / 256.0f;
    } else {
      colour[COLOUR_GREEN] = 0.0f;
    };
    if ( time >= 256 ) {
      colour[COLOUR_BLUE] = 0.0f;
    } else {
      colour[COLOUR_BLUE] = (256 - time) / 256.0f;
    };
 
    colour[COLOUR_ALPHA] = 1.0f;

    return colour;  
}


int main( int argc, char* args[] ) { 
  SDL_Window *app_window;
  SDL_GLContext app_glcontext;
  GLfloat *colour;

  int i;

  //Start SDL 
  SDL_Init( SDL_INIT_EVERYTHING ); 

  app_window = SDL_CreateWindow("I'm a window", 50,50,200,200, SDL_WINDOW_OPENGL);
  app_glcontext = SDL_GL_CreateContext(app_window);  
  SDL_GL_MakeCurrent(app_window, app_glcontext);

  printf("GL Version: %s\n",  glGetString(GL_VERSION));
  printf("GL Renderer: %s\n", glGetString(GL_RENDERER));
  printf("GL Vendor: %s\n", glGetString(GL_VENDOR));

  for(i=0;i<512;i++) {
    colour = colour_for_time(i);

    draw_colour(colour[COLOUR_RED], colour[COLOUR_GREEN], colour[COLOUR_BLUE]);
    SDL_GL_SwapWindow(app_window);

    SDL_Delay(200);
  }
 
  SDL_DestroyWindow(app_window);

  //Quit SDL SDL_Quit(); 
   return 0; 
}
