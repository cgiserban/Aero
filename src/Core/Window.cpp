#include "Window.h"

namespace Aero
{

    Window::Window(const WindowProps &props)
    {
        init(props);        
    }

    Window::~Window()
    {
    }

    Window* Window::create()
    {
        return new Window(WindowProps());
    }


    void Window::setVSync(bool enabled)
    {

        data.isVSyncEnabled = enabled;
    }

    void Window::init(const WindowProps &props)
    {
        data.title=props.title;
        data.width=props.width;
        data.height=props.width;
    }


}
