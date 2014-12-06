//
// C++ Interface: display
//
// Description:
//
//
// Author:  <>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#pragma once

#include <errorhandling.h>
#include "FrameworkOneApp.h"

/**
  Abstract class for handling displays \ openGL rendering contexts.
*/
class DisplayInterface {
public:
/**
  Get the current width of the display window
  @return The current width of the display issue.
*/
  virtual int getWidth() { return width; }
/**
  Get the current height of the display window
  @return The current height of the display issue.
*/
  virtual int getHeight() { return height; }

/**
  Performs a page-flip, swapping the back and front colour buffers.
*/
  virtual void swapBuffers() = 0;

/**
  Enters the main application loop, which will continue to execute until close is called. Use appMain() in the EngineApplication interface to implement the application specific portion of the main loop.
  @param app The object that will handle application code and event processing.
*/
  virtual void mainLoop(FrameworkOneApp &app) = 0;
/**
  Terminates the main loop at the end of its current cycle, and returns control to the point where mainLoop() was called.
*/
  virtual void close() = 0;

  virtual ~DisplayInterface() {}
protected:
  int width, height;
  /**/
};

/**
  Abstract root class for all display related errors. Individual implementations should define their own subclasses of this class.
*/
class DisplayError: public Error {};
