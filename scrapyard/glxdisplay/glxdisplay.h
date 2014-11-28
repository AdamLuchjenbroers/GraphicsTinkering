//
// C++ Interface: glxdisplay
//
// Description:
//
//
// Author:  <>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <system/display.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <unistd.h>

#define MFLAG_SINGLEBUFFER	0x0001
#define MFLAG_FULLSCREEN	0x0002
#define MFLAG_SQUAREVIEW	0x0004

/**
  Provides a GLX rendering context via a connection to an X Server
*/
class GLXDisplay : public DisplayInterface {
public:
  GLXDisplay(char *title);
  virtual void swapBuffers();
  virtual void mainLoop(EngineApplication &app);
  virtual void close();

private:
  Display 		*dpy;
  GLXContext	glcx;
  XVisualInfo	*xvi;
  Window		win;
  int			modeFlags;
  bool          closeFlag;
  int           oldX, oldY;

  void waitForMap();
  void processKeyEvent(XKeyEvent *ke, bool press, EngineApplication &app);
  void processButtonEvent(XButtonEvent *be, bool press, EngineApplication &app);
};

/**
  Basic GLX Display error, contains a simple text string describing the error.
*/
class GLXDisplayError : public DisplayError {
public:
  GLXDisplayError(const char *error);
  virtual std::string *toString();
  virtual ~GLXDisplayError() throw () ;
private:

  std::string *desc;
};

/*class GLXDisplayEvent : public DisplayEvent {
public:
  GLXDisplayEvent(XEvent *xev);
};*/
