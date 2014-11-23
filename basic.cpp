
#include "system/sdl2/sdl2display.h"
#include "system/display.h"

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
  DisplayInterface *display = new SDLDisplay("I'm a window", 300, 400);
  SDL_Event event;
  GLfloat *colour;

  int i;


  for(i=0;i<512;i++) {
    colour = colour_for_time(i);

    draw_colour(colour[COLOUR_RED], colour[COLOUR_GREEN], colour[COLOUR_BLUE]);
    display->swapBuffers();
 
    // Poll for events
    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)  {
         //Advance the counter, simple hack to quit app
         i=512;
      }
    }

    SDL_Delay(100);
  }
 
  delete display;
  return 0;
}
