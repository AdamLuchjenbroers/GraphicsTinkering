/***************************************************************************
 *   Copyright (C) 2007 by Adam Luchjenbroers                              *
 *   adam@luchjenbroers.com.au                                             *
 ***************************************************************************/
#include <system/display.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <windows.h>
#include <map>

LRESULT CALLBACK WinEvent(HWND, UINT, WPARAM, LPARAM);

#define WGL_WNDCLASSNAME        "wgldisplay"

//Derived using
//http://msdn2.microsoft.com/en-us/library/ms645540.aspx

#ifndef VK_XBUTTON1
#define VK_XBUTTON1 0x05
#endif
#ifndef VK_XBUTTON2
#define VK_XBUTTON2 0x06
#endif

#define VK_0 0x30
#define VK_9 0x39
#define VK_A 0x40
#define VK_Z 0x5A

//Pointer to WGLDisplay.
class PWGLDisplay;

/**
  Provides a GLX rendering context via a connection to an X Server
*/
class WGLDisplay : public SDLDisplay {
public:
  WGLDisplay(char *title, HINSTANCE hApplication, int showCmd);
  ~WGLDisplay();
  virtual void swapBuffers();
  virtual void mainLoop(FrameworkOneApp &app);
  virtual void close();

  LRESULT receiveEvent(UINT, WPARAM, LPARAM);
  static std::map<HWND, PWGLDisplay> Display;

  friend LRESULT CALLBACK WinEvent(HWND, UINT, WPARAM, LPARAM);
private:
  HGLRC hGLContext;
  HDC   hDevice;
  HWND  hWindow;
  HINSTANCE hApp;
  int   showCmd;
  bool  closeFlag;
  FrameworkOneApp* pApp;
  int oldX, oldY;

  bool keyState[256];

  void processKeyEvent(WPARAM key, bool press);
  unsigned int getModMask();
};

class PWGLDisplay {
public:
  PWGLDisplay() {
    display = 0;
  }
  PWGLDisplay(WGLDisplay *d) {
    display = d;
  }

  LRESULT receiveEvent(UINT u, WPARAM w, LPARAM l) {
    if (display) {
      return display->receiveEvent(u,w,l);
    }
    return 0;
  }
private:
  WGLDisplay *display;
};

/**
  Basic Windows GL display error, contains a simple text string describing the error.
*/
class WGLDisplayError : public DisplayError {
public:
  WGLDisplayError(const char *error, DWORD error);
  virtual std::string *toString();
  virtual ~WGLDisplayError() throw ();
private:

  std::string *desc;
};

