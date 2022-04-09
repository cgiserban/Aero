#include "GLFWLayer.h"
#include "UI/UI.h"

namespace Aero
{


    static void GLFWErrorCallback(int err, const char* desc)
    {
        AERO_CORE_ERROR("GLFW Error: ({0}): {1})", err, desc);
    }


    void GLFWLayer::onAttach()
    {
        window = glfwCreateWindow(props.width,props.height,props.title,nullptr,nullptr);

        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window,&data);
        setVSync(true);

        if (glewInit() != GLEW_OK)
            AERO_CORE_ERROR("Failed Initializing GLEW!");

        configCallbacks();

    }

    void GLFWLayer::onDetach()
    {

        glfwWindowShouldClose(window);
        glfwDestroyWindow(window);
        glfwTerminate();

    }

    void GLFWLayer::onUpdate()
    {
        glfwPollEvents();

        glClearColor(0.5,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);

    }

    void GLFWLayer::configCallbacks()
    {
        // Window Event Callback
        glfwSetErrorCallback(GLFWErrorCallback);
        //Resize Callback
        glfwSetWindowSizeCallback(window, [](GLFWwindow* w,int _w, int _h)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(w);
            WindowResizeEvent resize(_w,_h);
            data.EventCallback(resize);

            data.width = _w;
            data.height = _h;
        });
        //Close Callback
        glfwSetWindowCloseCallback(window, [](GLFWwindow* w)
        {
           WindowData& data = *(WindowData*)glfwGetWindowUserPointer(w);
           WindowCloseEvent close;
           data.EventCallback(close);

        });
        //Keyboard Callback
        glfwSetKeyCallback(window, [](GLFWwindow* w, int keycode, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(w);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(keycode,0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(keycode);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(keycode,1);
                    data.EventCallback(event);
                    break;
                }
            }

        });
        //Mouse Callback
        glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(w);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    MousePressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });
        //Scroll Callback
        glfwSetScrollCallback(window, [](GLFWwindow* w, double xoffset, double yoffset)
        {
           WindowData& data = *(WindowData*)glfwGetWindowUserPointer(w);
           MouseScrolledEvent event(yoffset);
           data.EventCallback(event);

        });
        //Move Callback
        glfwSetCursorPosCallback(window, [](GLFWwindow* w, double posX, double posY)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(w);
            MouseMovedEvent event(posX, posY);
            data.EventCallback(event);
        });
    }


    void GLFWLayer::onEvent(Event &event)
    {

    }

    void GLFWLayer::setVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }

    void GLFWLayer::init()
    {
        if (!glfwInit())
            AERO_CORE_ERROR("Failed Initializing GLFW!");
    }

}
