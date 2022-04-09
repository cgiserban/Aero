#pragma once

#include "Event.h"

namespace Aero
{

    class MousePressedEvent:public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
        EVENT_CLASS_TYPE(MouseButtonPressed);

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse Pressed Event:" << button;
            return ss.str();
        }

        int getButton() const {return button;}
        MousePressedEvent(int _button): button(_button) {}
    private:
        int button;
    };


    class MouseReleasedEvent:public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
        EVENT_CLASS_TYPE(MouseButtonReleased);

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse Released Event:" << button;
            return ss.str();
        }

        int getButton() const {return button;}

        MouseReleasedEvent(int _button): button(_button) {}

    private:
        int button;
    };


    class MouseMovedEvent:public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
        EVENT_CLASS_TYPE(MouseMoved);

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse Moved Event: X:" << posX << " Y:" << posY;
            return ss.str();
        }

        double getX() const {return posX;}
        double getY() const {return posY;}

        MouseMovedEvent(double _posX, double _posY): posX(_posX), posY(_posY){}

    private:
        double posX, posY;
    };

    class MouseScrolledEvent:public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
        EVENT_CLASS_TYPE(MouseScrolled);

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Mouse Scrolled Event: " << offsetY;
            return ss.str();
        }

        double getOffset() const {return offsetY;}

        MouseScrolledEvent(double _offsetY): offsetY(_offsetY){}
    private:
        double offsetY;
    };


}
