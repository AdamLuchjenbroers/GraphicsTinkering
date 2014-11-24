/*
 * Really basic shader from OpenGL SuperBible, chapter 2
 */

#include "system/sdl2/sdl2display.h"
#include "system/display.h"
#include "system/application.h"
#include "utilities/shader.h"

#define COLOUR_RED 0
#define COLOUR_GREEN 1
#define COLOUR_BLUE 2
#define COLOUR_ALPHA 3


class SB6_Chapter2 : public EngineApplication {
public:
	SB6_Chapter2();
	~SB6_Chapter2();

	bool appMain();
	void appInit();
	void appQuit();

private:
	DisplayInterface *display;

    GLuint program, vertexarray;
	Shader vertex = Shader("shader/sb2-vertex.sdr", GL_VERTEX_SHADER);
	Shader fragment = Shader("shader/sb2-fragment.sdr", GL_FRAGMENT_SHADER);
};

SB6_Chapter2::SB6_Chapter2() {
	this->display = NULL;

	this->program = glCreateProgram();
	glAttachShader(this->program, this->vertex);
    glAttachShader(this->program, this->fragment);
    glLinkProgram(this->program);

    glGenVertexArrays(1, &this->vertexarray);
    glBindVertexArray(this->vertexarray);
}

SB6_Chapter2::~SB6_Chapter2() {
	if (this->display != NULL) {
		delete this->display;
	}
}

void SB6_Chapter2::appInit() {
	this->display = new SDLDisplay("Chapter 2 - A Point", 300, 400);

}

bool SB6_Chapter2::appMain() {
	GLfloat *colour;

	glUseProgram(this->program);
    glDrawArrays(GL_POINTS, 0, 1);

    display->swapBuffers();

    display->mainLoop(*this);

    SDL_Delay(100);
    return true;
}

void SB6_Chapter2::appQuit() {
	// Fast forward the colour cascade to the last index
	this->colourIndex = 512;
}



int main( int argc, char* args[] ) { 
  EngineApplication *thisApp = new BasicApp();

  thisApp->appInit();

  while (thisApp->appMain()) { };
 
  delete thisApp;
  return 0;
}
