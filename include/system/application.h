#pragma once

#include <errorhandling.h>
#include <system/constants.h>
#include <string>

class EngineApplication {
public:
	virtual ~EngineApplication() {};

    /** Main body of application code, called once per iteration of the main display loop */
    virtual bool appMain() = 0;
    /** Called immediately after the display has been initialised to allow the application to perform any setup it may require. */
    virtual void appInit() = 0;

    /**
        Called whenever the display window is resized.
        @param newX The new width of the display window.
        @param newY The new height of the display window.
    */
    virtual void resizeWindow(int newX, int newY) {}

    /**
        Called whenever a key is pressed
        @param key Enumerated value representing the key that was pressed. Alphanumeric keys pass KEY_ALPHANUMERIC and pass the character in using alpha.
        @param modmask Bitfield representing the keyboard modifier keys that were pressed.
        @param press Boolean value, true if the key is being pressed, false if released.
        @param alpha The alphanumeric representation of the key pressed (0 if invalid)
    */
    virtual void keyEvent(Key key, unsigned int modmask, bool press, char alpha) {}

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
        @param modmask Bitfield representing the current status of all mouse buttons.
        @param x X co-ordinate where this button was pressed.
        @param y Y co-ordinate where this button was pressed.
    */
    virtual void mouseMovementEvent(unsigned int modmask, int x, int y, int oldX, int oldY) {};

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

