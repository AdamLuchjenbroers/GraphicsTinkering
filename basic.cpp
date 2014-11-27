
#include "fw1/fw1.h"

#define COLOUR_RED 0
#define COLOUR_GREEN 1
#define COLOUR_BLUE 2
#define COLOUR_ALPHA 3


class BasicApp : public EngineApplication {
public:
	BasicApp();
	~BasicApp();

	bool appMain();
	void appInit();
	void appQuit();

private:
	DisplayInterface *display;
	int colourIndex;

	bool running;

	void draw_colour(GLfloat r, GLfloat g, GLfloat b);
	GLfloat *colour_for_time(int time);
};

BasicApp::BasicApp() {
	this->display = NULL;
	this->colourIndex = 0;
	this->running = true;
}

BasicApp::~BasicApp() {
	if (this->display != NULL) {
		delete this->display;
	}
}

void BasicApp::appInit() {
	this->display = new SDLDisplay("I'm a window", 300, 400);
}

bool BasicApp::appMain() {
	GLfloat *colour;

	if (this->colourIndex >= 512) {
		// We're done, exit
		return false;
	}

    colour = colour_for_time(this->colourIndex);
    this->colourIndex++;

    draw_colour(colour[COLOUR_RED], colour[COLOUR_GREEN], colour[COLOUR_BLUE]);

    display->swapBuffers();

    display->mainLoop(*this);

    SDL_Delay(100);
    return this->running;
}

void BasicApp::appQuit() {
	this->running = false;
}

void BasicApp::draw_colour(GLfloat r, GLfloat g, GLfloat b) {
    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_APPLICATION, "[%i] R:%f G:%f B:%f\n", this->colourIndex, r, g, b);

    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

GLfloat *BasicApp::colour_for_time(int time) {
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
  EngineApplication *thisApp = new BasicApp();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}
