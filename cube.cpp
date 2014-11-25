/*
 * Primitive OpenGL program that generates a cube that rotates once
 */

#include "system/sdl2/sdl2display.h"
#include "system/display.h"
#include "system/application.h"

class CubeApp : public EngineApplication {
public:
	CubeApp(int rotations);
	~CubeApp();

	bool appMain();
	void appInit();
	void appQuit();

private:
	DisplayInterface *display;
	int remainingRotations;
        float currentAngle;

	void draw_colour(GLfloat r, GLfloat g, GLfloat b);
	GLfloat *colour_for_time(int time);
};

CubeApp::CubeApp(int rotations) {
   this->remainingRotations = rotations;
   this->currentAngle = 0.0f;

   this->display = NULL;
}

CubeApp::~CubeApp() {
	if (this->display != NULL) {
		delete this->display;
	}
}

void CubeApp::appInit() {
	this->display = new SDLDisplay("I'm a window", 1200, 1200);
}

bool CubeApp::appMain() {
	if (this->remainingRotations < 0) {
		return false;
	}

	// Clear colour buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();

    // Setup Cube Position           // Move Into The Screen And Left
    //glRotatef(this->currentAngle,0.0f,1.0f,0.0f);

    //glTranslatef(0.0f,0.0f,-6.0f);

    printf("Angle: %f, (%i rotations remaining)\n", this->currentAngle, this->remainingRotations);
    /*glBegin(GL_QUADS);

      glColor3f(1.0f, 1.0f, 1.0f);
      // Front Face
      glVertex3f(-1.0f,1.0f,1.0f);
      glVertex3f(-1.0f,1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f,1.0f);

      // Back Face
      glVertex3f(1.0f,1.0f,1.0f);
      glVertex3f(1.0f,-1.0f,1.0f);
      glVertex3f(1.0f,-1.0f,-1.0f);
      glVertex3f(1.0f,1.0f,-1.0f);

      glColor3f(0.0f, 1.0f, 0.0f);
      // Left Face
      glVertex3f(1.0f,1.0f,1.0f);
      glVertex3f(-1.0f,1.0f,1.0f);
      glVertex3f(-1.0f,1.0f,-1.0f);
      glVertex3f(1.0f,1.0f,-1.0f);

      // Right Face
      glVertex3f(1.0f,-1.0f,1.0f);
      glVertex3f(1.0f,-1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glVertex3f(-1.0f,-1.0f,1.0f);
    glEnd();*/

    this->currentAngle += 1.0f;
    if (this->currentAngle >= 360.0f) {
    	this->currentAngle = 0.0f;
    	this->remainingRotations--;
    }
    display->swapBuffers();
    display->mainLoop(*this);

    SDL_Delay(100);
    return true;
}

void CubeApp::appQuit() {
	// Fast forward the colour cascade to the last index
	this->remainingRotations = -1;
}

int main( int argc, char* args[] ) {
  EngineApplication *thisApp = new CubeApp(2);

  thisApp->appInit();

  while (thisApp->appMain()) { };

  delete thisApp;
  return 0;
}




