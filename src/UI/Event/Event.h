#pragma once
#include <functional>
#include <sstream>
#include <string>


#define BIT(x) (1<<x)

namespace Aero
{
    enum class EventType
    {
        None = 0,
        WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMoved,
        KeyPressed,KeyReleased,
        MouseButtonPressed,MouseButtonReleased,MouseMoved,MouseScrolled,
        AppTick,AppUpdate,AppRender
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput       = BIT(1),
        EventCategoryKeyboard    = BIT(2),
        EventCategoryMouse       = BIT(3)
    };

    class Event
    {
        friend class EventDispatcher;

    public:
        virtual EventType getEventType() const = 0;
        virtual int getCategoryFlags() const = 0;
        virtual const char* getName() const = 0;
        virtual std::string toString() const {return getName();}

        bool isInCategory(EventCategory cat){
            return getCategoryFlags() & cat;
        }

        bool handled = false;
    };

    class EventDispatcher
    {
        template <typename T>
        using EventFn = std::function<bool(T&)>;

    public:
        EventDispatcher(Event& _event) : event(_event){} ;

        template <typename T>
        bool dispatch(EventFn<T> func)
        {
            if (event.getEventType() == T::getStaticType())
            {
                event.handled = func(*(T*)&event);
                return true;
            }
            return false;
        }

    private:
        Event& event;
    };

#define EVENT_CLASS_TYPE(type) static EventType getStaticType(){return EventType::type;} \
                               virtual EventType getEventType() const override {return getStaticType();} \
                               virtual const char* getName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override {return category;}

}

