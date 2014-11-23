#pragma once

#define KEYMOD_SHIFT  0x0001
#define KEYMOD_CAPSLOCK 0x0002
#define KEYMOD_CTRL   0x0004
#define KEYMOD_ALT    0x0008
//Alt is a synonym for Meta1
#define KEYMOD_META1  0x0008
#define KEYMOD_META2  0x0010
#define KEYMOD_META3  0x0020
#define KEYMOD_META4  0x0040
#define KEYMOD_META5  0x0080

//These values will often share the bitfield with the keyboard data.
//So map them such that they do not conflict with KEYMOD_*
#define MOUSE_BUTTON1 0x0100
#define MOUSE_BUTTON2 0x0200
#define MOUSE_BUTTON3 0x0400
#define MOUSE_BUTTON4 0x0800
#define MOUSE_BUTTON5 0x1000

enum Key {
    KEY_ALPHANUMERIC,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_RSHIFT,
    KEY_LSHIFT,
    KEY_TAB,
    KEY_LCTRL,
    KEY_RCTRL,
    KEY_LALT,
    KEY_RALT,
    KEY_INSERT,
    KEY_DELETE,
    KEY_HOME,
    KEY_END,
    KEY_PAGEUP,
    KEY_PAGEDOWN,
    KEY_ENTER,
    KEY_TILDE,
    KEY_ESCAPE,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_PRINTSCREEN,
    KEY_PAUSE,
    KEY_UNKNOWN //Default.
};
