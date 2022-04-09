#pragma once

#include "Event.h"

namespace Aero{

    class KeyEvent:public Event
    {
    public:

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

        int getKeyCode() const {return keyCode;}

    protected:
        KeyEvent(int _keyCode) : keyCode(_keyCode){};
        int keyCode;
    };

    class KeyPressedEvent:public KeyEvent
    {
    public:

        EVENT_CLASS_TYPE(KeyPressed);

        KeyPressedEvent(int _keyCode, int _repeatCount): KeyEvent(_keyCode), repeatCount(_repeatCount){};
        int getRepeatCount() const {return repeatCount;}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Key Pressed Event:" << keyCode << " " << repeatCount << "times";
            return ss.str();
        }
    private:
        int repeatCount;
    };

    class KeyReleasedEvent:public KeyEvent
    {
    public:

        EVENT_CLASS_TYPE(KeyReleased);

        KeyReleasedEvent(int _keyCode): KeyEvent(_keyCode){};

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Key Released Event:" << keyCode;
            return ss.str();
        }
    };


}

