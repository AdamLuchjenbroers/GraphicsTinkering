#pragma once

#include <errorhandling.h>
#include <SDL2/SDL.h>
#include <string>
#include <stdlib.h>

/** FrameworkOneApp Husk Class - All Apps should extend this class to take advantage of existing framework and tools
    @brief A husk class providing the scaffolding for a FrameworkOne app
*/
class FrameworkOneApp {
public:
	virtual ~FrameworkOneApp() {};

    /** Main body of application code, called once per iteration of the main display loop */
    virtual bool appMain() = 0;
    /** Called immediately after the display has been initialised to allow the application to perform any setup it may require. */
    virtual void appInit() = 0;

    /** Called when an event is received requesting an application exit */
    virtual void appQuit() { exit(0); };

    /**
        Called whenever the display window is resized.
        @param newX The new width of the display window.
        @param newY The new height of the display window.
    */
    virtual void resizeWindow(int newX, int newY) {}

    /**
        Called whenever a key is pressed
        @param key Enumerated value representing the key that was pressed. Alphanumeric keys pass KEY_ALPHANUMERIC and pass the character in using alpha.
        @param press Boolean value, true if the key is being pressed, false if released.
    */
    virtual void keyEvent(SDL_Keysym &key, bool press) {}

    /**
        Called whenever a mouse button is pressed.
        @param button The button that has been pressed/released (uses the mask values to represent each button).
        @param modmask Bitfield representing the current status of all mouse buttons.
        @param press Boolean value, true if the button is being pressed, false if released.
        @param x X co-ordinate where this button was pressed.
        @param y Y co-ordinate where this button was pressed.
    */
    virtual void mouseButtonEvent(int button, unsigned int modmask, bool press, int x, int y) {};

    /**
        Called whenever the mouse is moved.
        @param buttons Bitfield representing the current status of all mouse buttons.
        @param x X co-ordinate where this button was pressed.
        @param y Y co-ordinate where this button was pressed.
        @param offsetX Change in the X position.
        @param offsetY Change in the Y position.
    */
    virtual void mouseMovementEvent(Uint8 buttons, int x, int y, int offsetX, int offsetY) {};
};

/**
    Root class for all application related errors. Individual implementations should define their own subclasses of this class.
*/
class ApplicationError : public Error {
public:
    ApplicationError(char *text);
    ~ApplicationError() throw ();

    std::string *toString();
private:
    std::string *desc;
};/**/

