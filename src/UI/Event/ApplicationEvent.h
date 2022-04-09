#pragma once

#include "Event.h"

namespace Aero
{

    class WindowCloseEvent: public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
        EVENT_CLASS_TYPE(WindowClose);

        WindowCloseEvent(){}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Window Closed";
            return ss.str();
        }

    };


    class WindowResizeEvent:public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
        EVENT_CLASS_TYPE(WindowResize);

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "Window Resize Event: w:" << width << ", h:" << height;
            return ss.str();
        }

        WindowResizeEvent(int _width, int _height):width(_width), height(_height){}

        unsigned int getWidth() const {return width;}
        unsigned int getHeight() const {return height;}

    private:
        unsigned int width;
        unsigned int height;
    };

    class WindowFocusEvent: public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryApplication);
        EVENT_CLASS_TYPE(WindowFocus);

        WindowFocusEvent(){inFocus = true;}

    private:
        bool inFocus;
    };

    class WindowLostFocusEvent: public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryApplication);
        EVENT_CLASS_TYPE(WindowLostFocus);

        WindowLostFocusEvent(){inFocus = false;}

    private:
        bool inFocus;
    };


}
