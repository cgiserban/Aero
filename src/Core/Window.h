#pragma once

#include "Core/Log.h"
#include "UI/Event/Event.h"


namespace Aero

{
    using EventCallbackFn = std::function<void(Event&)>;

    struct WindowProps
    {
        const char* title;
        unsigned int width;
        unsigned int height;

        WindowProps(const char* _title="Aero v1.0", unsigned int _width = 1280, unsigned int _height = 720):
            title(_title), width(_width), height(_height){}
    };

    struct WindowData
    {
        const char* title;
        unsigned int width = 1280;
        unsigned int height = 720;
        bool isVSyncEnabled;
        EventCallbackFn EventCallback;
    };

    class Window
    {
    public:

        Window(const WindowProps& props);
        ~Window();

        static Window* create();
        virtual unsigned int getWidth(){return data.width;}
        virtual unsigned int getHeight(){return data.height;}


        virtual void setVSync(bool enabled);
        bool isVSync() const {return data.isVSyncEnabled;}

        WindowData data;
    private:

        void init(const WindowProps &props);

    };
}

