/***************************************************************************
 *   Copyright (C) 2007 by Adam Luchjenbroers                              *
 *   adam@luchjenbroers.com.au                                             *
 ***************************************************************************/
 
#include "wgldisplay.h"
#include <cstdio>

std::map<HWND, PWGLDisplay> WGLDisplay::Display;

LRESULT CALLBACK WinEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  PWGLDisplay win = WGLDisplay::Display[hwnd];
  
  switch (msg) {
    case WM_NCCREATE: case WM_CREATE:
      return true;
  }
  //Route the message to the correct window.
  return win.receiveEvent(msg,wParam,lParam);
}

/**
   Instantiates a new OpenGL display window.
   @param title The title for the new window.
   @param hApplication The Instance handle for the running application.
   @param cmd The Show Command value provided by Windows.
*/
WGLDisplay::WGLDisplay(char *title, HINSTANCE hApplication, int cmd) {
  PIXELFORMATDESCRIPTOR glPFD;
  GLuint glPixelFormat;

  //Initialise to 0 so we can check if they'be been initialised
  hGLContext = 0;
  hWindow = 0;
  hDevice = 0;
  pApp = 0;

  //Check if the window class has already been registered
  if(!GetClassInfo(hApp, WGL_WNDCLASSNAME, NULL)) {
    WNDCLASSEX window;
    
    window.hInstance     = hApplication;
    window.lpszClassName = WGL_WNDCLASSNAME;
    window.lpfnWndProc   = (WNDPROC) WinEvent; 
    window.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window.cbSize        = sizeof (WNDCLASSEX);
    window.cbClsExtra    = 0;
    window.cbWndExtra    = 0;

    window.hIcon         = NULL; //LoadIcon (NULL, IDI_APPLICATION);
    window.hIconSm       = NULL; //LoadIcon (NULL, IDI_APPLICATION);
    window.hCursor       = LoadCursor (NULL, IDC_ARROW);
    window.lpszMenuName  = NULL;                 
    window.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    if (!RegisterClassEx(&window)) {
      throw new WGLDisplayError("Unable to register Window Class", GetLastError());
    }
  }
  hApp   = hApplication;
  width  = 400;
  height = 400;
   
  hWindow = CreateWindowEx(
    WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, 
    WGL_WNDCLASSNAME, 
    title,
    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_CAPTION, 
    CW_USEDEFAULT, 
    CW_USEDEFAULT, 
    width, 
    height, 
    NULL, 
    NULL, 
    hApp, 
    NULL 
  );
  
  if (!hWindow) {
    throw new WGLDisplayError("Unable to create window", GetLastError());
  }  
  //Register this handle so events can be routed to it.
  Display[hWindow] = *(new PWGLDisplay(this));

  hDevice = GetDC(hWindow);
  if (!hDevice) {
    throw new WGLDisplayError("Unable to get Device Context", GetLastError());
  }
  
  glPFD.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
  glPFD.nVersion   = 1;
  glPFD.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  glPFD.iPixelType = PFD_TYPE_RGBA;
  glPFD.cColorBits = 32;
  // Ignore color bits, set as appropriate
  glPFD.cRedBits   = 0; glPFD.cRedShift   = 0;
  glPFD.cBlueBits  = 0; glPFD.cBlueShift  = 0;
  glPFD.cGreenBits = 0; glPFD.cGreenShift = 0;
  glPFD.cAlphaBits = 0; glPFD.cAlphaShift = 0;
  //No Accumulation buffer.
  glPFD.cAccumBits      = 0;
  glPFD.cAccumRedBits   = 0; glPFD.cAccumBlueBits  = 0;
  glPFD.cAccumGreenBits = 0; glPFD.cAccumAlphaBits = 0;
  
  glPFD.cDepthBits   = 16;
  glPFD.cStencilBits = 8;
  glPFD.cAuxBuffers  = 0;
  
  //Reserved or depreciated fields
  glPFD.iLayerType    = PFD_MAIN_PLANE;
  glPFD.bReserved     = 0;
  glPFD.dwLayerMask   = 0;
  glPFD.dwVisibleMask = 0;
  glPFD.dwDamageMask  = 0;

  glPixelFormat = ChoosePixelFormat(hDevice, &glPFD);
  if (!glPixelFormat) {
    //Try to get something simpler..
    glPFD.cColorBits = 16;
    glPFD.cDepthBits = 8;
    glPixelFormat = ChoosePixelFormat(hDevice, &glPFD);
  }
  if (!glPixelFormat) {
    throw WGLDisplayError("Unable to select a suitable pixel format", GetLastError());
  }
                      
  if (!SetPixelFormat(hDevice, glPixelFormat, &glPFD)) {
    throw WGLDisplayError("Unable to set pixel format", GetLastError());
  }                    

  hGLContext = wglCreateContext(hDevice);
  if (!hGLContext) {
    throw WGLDisplayError("Unable to create OpenGL context", GetLastError());
  }
  
  showCmd = cmd;
  closeFlag = false;  
  
  ShowWindow (hWindow, showCmd);
  
  for(int i=0;i<256;i++) {
    keyState[i] = false;        
  }
}

void WGLDisplay::swapBuffers() {
  SwapBuffers(hDevice);
}

void WGLDisplay::mainLoop(FrameworkOneApp &app) {
  if (pApp) {
    throw WGLDisplayError("Main loop still being executed", 21); //ERR_NOT_READY
  }
     
  pApp = &app;

  if (!wglMakeCurrent(hDevice, hGLContext)) {
    throw WGLDisplayError("Unable to set current OpenGL context", GetLastError());
  }
  //MessageBox(NULL, "BOO!", "Debugging", MB_ICONINFORMATION);
   
  ShowWindow (hWindow, showCmd);
  showCmd = SW_SHOW;
  SetForegroundWindow(hWindow);
  SetFocus(hWindow);    
  
  app.appInit();
     
  while (!closeFlag) {
    MSG message;
    
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    
    if (PeekMessage(&message,NULL,0,0,PM_REMOVE)) {
      DispatchMessage(&message);
    }  
  
    app.appMain();
  }
  pApp = 0;     
}

unsigned int WGLDisplay::getModMask() {
  unsigned int modmask; 
  
  modmask = 0;
  if (keyState[VK_SHIFT])    { modmask |= KEYMOD_SHIFT; }
  if (keyState[VK_CONTROL])  { modmask |= KEYMOD_CTRL; }
  if (keyState[VK_MENU])     { modmask |= KEYMOD_ALT; }
  if (keyState[VK_CAPITAL])  { modmask |= KEYMOD_CAPSLOCK; }
  if (keyState[VK_LBUTTON])  { modmask |= MOUSE_BUTTON1; }
  if (keyState[VK_RBUTTON])  { modmask |= MOUSE_BUTTON2; }
  if (keyState[VK_MBUTTON])  { modmask |= MOUSE_BUTTON3; }
  if (keyState[VK_XBUTTON1]) { modmask |= MOUSE_BUTTON4; }
  if (keyState[VK_XBUTTON2]) { modmask |= MOUSE_BUTTON5; }
  
  return modmask;
}     

void WGLDisplay::processKeyEvent(WPARAM key, bool press) {
  unsigned int modmask;   
     
  //Check for repeat presses
  if (keyState[key] == press) {
    return;
  }
  keyState[key] = press;
  
  modmask = getModMask();
  
  if(!keyState[VK_SHIFT] && (key >= VK_0 && key <= VK_9)) {
    char in = '0' + key - VK_0;
    
    pApp->keyEvent(KEY_ALPHANUMERIC, modmask, press, in);
    return;   
  }
  
  if(!key >= VK_A && key <= VK_Z) {
    char in = key - VK_A;
    
    if (keyState[VK_SHIFT]) {
      in += 'A';
    } else {
      in += 'a';
    }
    
    pApp->keyEvent(KEY_ALPHANUMERIC, modmask, press, in);
    return;   
  }
  
    //FIXME Incomplete list of keys
  switch (key) {
    case VK_UP:
      pApp->keyEvent(KEY_UP, modmask, press, 0);
      break;
    case VK_DOWN:
      pApp->keyEvent(KEY_DOWN, modmask, press, 0);
      break;
    case VK_LEFT:
      pApp->keyEvent(KEY_LEFT, modmask, press, 0);
      break;
    case VK_RIGHT:
      pApp->keyEvent(KEY_RIGHT, modmask, press, 0);
      break;
    case VK_ESCAPE:
      pApp->keyEvent(KEY_ESCAPE, modmask, press, 0);
      break;    
    case VK_F1:
      pApp->keyEvent(KEY_F1, modmask, press, 0);
      break;     
    case VK_F2:
      pApp->keyEvent(KEY_F2, modmask, press, 0);
      break;
    case VK_F3:
      pApp->keyEvent(KEY_F3, modmask, press, 0);
      break;
    case VK_F4:
      pApp->keyEvent(KEY_F4, modmask, press, 0);
      break;
    case VK_F5:
      pApp->keyEvent(KEY_F5, modmask, press, 0);
      break;
    case VK_F6:
      pApp->keyEvent(KEY_F6, modmask, press, 0);
      break;           
    case VK_F7:
      pApp->keyEvent(KEY_F7, modmask, press, 0);
      break;
    case VK_F8:
      pApp->keyEvent(KEY_F8, modmask, press, 0);
      break;
    case VK_F9:
      pApp->keyEvent(KEY_F9, modmask, press, 0);
      break;
    case VK_F10:
      pApp->keyEvent(KEY_F10, modmask, press, 0);
      break;
    case VK_F11:
      pApp->keyEvent(KEY_F11, modmask, press, 0);
      break;   
    case VK_F12:
      pApp->keyEvent(KEY_F12, modmask, press, 0);
      break;  
    //FIXME: Missing ENTER et al. 
     
  }
}

void WGLDisplay::close() {
  closeFlag = true;
}

LRESULT WGLDisplay::receiveEvent(UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_CLOSE: 
      PostQuitMessage(0);
      closeFlag = true;
      return 0;      
    case WM_SIZE:
      width  = LOWORD(lParam);
      height = HIWORD(lParam);
      if (pApp) { pApp->resizeWindow(width,height); }
      return 0;
    case WM_KEYDOWN: //case WM_SYSKEYDOWN:
      processKeyEvent(wParam, true);
      return 0;
    case WM_KEYUP:// case WM_SYSKEYUP:
      processKeyEvent(wParam, false);
      return 0;
    case WM_MOUSEMOVE:
      pApp->mouseMovementEvent(getModMask(), LOWORD(lParam), HIWORD(lParam), oldX, oldY);
      oldX = LOWORD(lParam);
      oldY = HIWORD(lParam);
      return 0;
    case WM_LBUTTONDOWN:
      keyState[VK_LBUTTON] = true;
      pApp->mouseButtonEvent(MOUSE_BUTTON1, getModMask(), true, LOWORD(lParam), HIWORD(lParam));
      break;
    case WM_LBUTTONUP:
      keyState[VK_LBUTTON] = false;
      pApp->mouseButtonEvent(MOUSE_BUTTON1, getModMask(), false, LOWORD(lParam), HIWORD(lParam));
      break;
    case WM_RBUTTONDOWN:
      keyState[VK_RBUTTON] = true;
      pApp->mouseButtonEvent(MOUSE_BUTTON2, getModMask(), true, LOWORD(lParam), HIWORD(lParam));
      break;
    case WM_RBUTTONUP:
      keyState[VK_RBUTTON] = false;
      pApp->mouseButtonEvent(MOUSE_BUTTON2, getModMask(), false, LOWORD(lParam), HIWORD(lParam));
      break;
    case WM_MBUTTONDOWN:
      keyState[VK_MBUTTON] = true;
      pApp->mouseButtonEvent(MOUSE_BUTTON3, getModMask(), true, LOWORD(lParam), HIWORD(lParam));
      break;
    case WM_MBUTTONUP:
      keyState[VK_MBUTTON] = false;
      pApp->mouseButtonEvent(MOUSE_BUTTON3, getModMask(), false, LOWORD(lParam), HIWORD(lParam));
      break;
  }
  return DefWindowProc(hWindow, msg, wParam, lParam);
}


WGLDisplay::~WGLDisplay() {
  if (hGLContext) { //TODO: Implement error logging (requires logging mechanism)
    wglMakeCurrent(NULL,NULL);
    wglDeleteContext(hGLContext);
    hGLContext = 0;
  }
  if (hDevice) {
    ReleaseDC(hWindow, hDevice);
    hDevice = 0;
  }
  if (hWindow) {
    DestroyWindow(hWindow);
    hWindow = 0;
  }
  UnregisterClass(WGL_WNDCLASSNAME,hApp);
}

/* =================
   WGLDisplayError
   ================= */
/**
  Creates a new WGLDisplayError instance with the provided error text.
  @param  text  A text description of the error.
  @param  error The Windows API Error code for this error.
	
*/
WGLDisplayError::WGLDisplayError(const char *text, DWORD error) {
  char errCode[16];

  std::snprintf(errCode, 16, " (0x%08lX)", error);
  //TODO: Append error code to the end as a hexidecimal number.
  desc = new std::string(text);
  *desc += errCode;
}

std::string *WGLDisplayError::toString() {
  //Return a copy, as we expect the caller to take care of the reference here.
  return new std::string(*desc);
}

WGLDisplayError::~WGLDisplayError() throw () {
  delete desc;
}
