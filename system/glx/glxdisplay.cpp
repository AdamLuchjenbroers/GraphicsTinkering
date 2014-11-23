//
// C++ Implementation: glxdisplay
//
// Description:
//
//
// Author:  <>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "glxdisplay.h"

static GLint glxDblAttribs[] = {GLX_RGBA, GLX_DOUBLEBUFFER, GLX_DEPTH_SIZE, 16, None};
static GLint glxSglAttribs[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, None};

GLXDisplay::GLXDisplay(char *title) {
  XSetWindowAttributes attr;

  if (!(dpy = XOpenDisplay(0))) {
    throw GLXDisplayError("initDisplay: Unable to open display");
  }

  xvi = glXChooseVisual(dpy,DefaultScreen(dpy), glxDblAttribs);
  if (!xvi) {
    xvi = glXChooseVisual(dpy,DefaultScreen(dpy), glxSglAttribs);
    if (!xvi) {
      throw GLXDisplayError("initDisplay: Unable to obtain appropriate visual");
    }
    modeFlags = modeFlags | MFLAG_SINGLEBUFFER;
  }

  if (!(glcx = glXCreateContext(dpy,xvi,0,GL_TRUE))) {
    throw GLXDisplayError("initDisplay: Unable to create GLX context");
  }

  attr.colormap = XCreateColormap(dpy,RootWindow(dpy,xvi->screen),xvi->visual,AllocNone);
  attr.border_pixel = 0;
  attr.event_mask = StructureNotifyMask | KeyPressMask | PointerMotionMask | ButtonPressMask;
  if(!attr.colormap) {
	  throw GLXDisplayError("initDisplay: Request for Colormap failed");
  }

  win = XCreateWindow(dpy,RootWindow(dpy, xvi->screen), 0, 0, 400, 400, 0,
        xvi->depth, InputOutput, xvi->visual, CWBorderPixel|CWColormap|CWEventMask, &attr);
  modeFlags |= MFLAG_SQUAREVIEW;
  if (!win) {
	  throw GLXDisplayError("initDisplay: Failed to create window\n");

  }

  XSetStandardProperties(dpy,win,title,title,0,NULL,0,NULL);
  XMapWindow(dpy,win);

  waitForMap();
  if (!glXMakeCurrent(dpy,win,glcx)) {
	  throw GLXDisplayError("initDisplay: Failed to set OpenGL context\n");
  }

  width = height = 400;

  closeFlag = false;
}

void GLXDisplay::waitForMap() {
  for(;;) {
	XEvent e;
	XNextEvent(dpy, &e);
	if (e.type == MapNotify)
	  break;
  }
}

void GLXDisplay::mainLoop(EngineApplication &app) {

    if(XPending(dpy) > 0) {
        XEvent xev;

        XNextEvent(dpy, &xev);
        switch(xev.type) {
            case ConfigureNotify:
                width = xev.xconfigure.width;
                height = xev.xconfigure.height;
                app.resizeWindow(width, height);
                break;
            case KeyPress:
                processKeyEvent(&(xev.xkey), true, app);
                break;
            case KeyRelease:
                processKeyEvent(&(xev.xkey), false, app);
                break;
            case MotionNotify:
                app.mouseMovementEvent(xev.xmotion.state & 0x1fff, xev.xmotion.x, xev.xmotion.y, oldX, oldY);
                oldX = xev.xmotion.x;
                oldY = xev.xmotion.y;
                break;
            case ButtonPress:
                processButtonEvent(&(xev.xbutton), true, app);
                break;
            case ButtonRelease:
                processButtonEvent(&(xev.xbutton), false, app);
                break;
	}
    }
}


void GLXDisplay::processButtonEvent(XButtonEvent *be, bool press, EngineApplication &app) {
  int button, modmask;

  //Since X uses the same bitfield values, simply mask out the relevant bits
  //without needing to translate anything.
  modmask = (be->state & 0x1fff);

  //Button1-Button5 map to values 1-5. The mask values for them map to 8-12.
  //While code for each button could be written out, it is possible to get away
  //with this...
  button = (1 << (be->button + 7));

  app.mouseButtonEvent(button, modmask, press, be->x, be->y);
}

void GLXDisplay::processKeyEvent(XKeyEvent *ke, bool press, EngineApplication &app) {
  char alpha;
  int modmask = 0;

  //Since X uses the same bitfield values, simply mask out the relevant bits
  //without needing to translate anything.
  modmask = (ke->state & 0x1fff);

  //FIXME Incomplete list of keys

  switch(XLookupKeysym(ke,0)) {
    case XK_Up:
      app.keyEvent(KEY_UP, modmask, press, (char) 0);
      break;
    case XK_Down:
      app.keyEvent(KEY_DOWN, modmask, press,(char) 0);
      break;
    case XK_Left:
      app.keyEvent(KEY_LEFT, modmask, press,(char) 0);
      break;
    case XK_Right:
      app.keyEvent(KEY_RIGHT, modmask, press,(char) 0);
      break;
    case XK_Escape:
      app.keyEvent(KEY_ESCAPE, modmask, press,(char) 0);
      break;
    case XK_F1:
      app.keyEvent(KEY_F1, modmask, press,(char) 0);
      break;
    case XK_F2:
      app.keyEvent(KEY_F2, modmask, press,(char) 0);
      break;
    case XK_F3:
      app.keyEvent(KEY_F3, modmask, press,(char) 0);
      break;
    case XK_F4:
      app.keyEvent(KEY_F4, modmask, press,(char) 0);
      break;
    case XK_F5:
      app.keyEvent(KEY_F5, modmask, press,(char) 0);
      break;
    case XK_F6:
      app.keyEvent(KEY_F6, modmask, press,(char) 0);
      break;
    case XK_F7:
      app.keyEvent(KEY_F7, modmask, press,(char) 0);
      break;
    case XK_F8:
      app.keyEvent(KEY_F8, modmask, press,(char) 0);
      break;
    case XK_F9:
      app.keyEvent(KEY_F9, modmask, press,(char) 0);
      break;
    case XK_F10:
      app.keyEvent(KEY_F10, modmask, press,(char) 0);
      break;
    case XK_F11:
      app.keyEvent(KEY_F11, modmask, press,(char) 0);
      break;
    case XK_F12:
      app.keyEvent(KEY_F12, modmask, press,(char) 0);
      break;
    case XK_Print:
      app.keyEvent(KEY_PRINTSCREEN, modmask, press,(char) 0);
      break;
    case XK_Pause:
      app.keyEvent(KEY_PAUSE, modmask, press,(char) 0);
      break;

    //TODO KeyEvents - LShift, RShift, Tab, LCtrl, RCtrl, LAlt, RAlt, Ins, Del, Home, PgUp, PgDn
    default:
      if ( XLookupString(ke, &alpha, 1, NULL, NULL) ) {
        app.keyEvent(KEY_ALPHANUMERIC, modmask, press, alpha);
      } else {
        app.keyEvent(KEY_UNKNOWN, modmask, press, (char) 0);
      }
      break;
  }
}

void GLXDisplay::close() {
  closeFlag = true;
}

void GLXDisplay::swapBuffers() {
  if (modeFlags & MFLAG_SINGLEBUFFER) {
    return;
  }
  glXSwapBuffers(dpy,win);
};

/* =================
   GLXDisplayError
   ================= */
/**
  Creates a new GLError instance with the provided error text.
	@param 	text		A text description of the error.
*/
GLXDisplayError::GLXDisplayError(const char *text) {
  desc = new std::string(text);
}

std::string *GLXDisplayError::toString() {
  //Return a copy, as we expect the caller to take care of the reference here.
  return new std::string(*desc);
}

GLXDisplayError::~GLXDisplayError() throw () {
  delete desc;
}

