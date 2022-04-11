#include "GLFWLayer.h"
#include "UI/UI.h"


namespace Aero
{
    #define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)


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

        AERO_CORE_INFO("OpenGL:{0}", (const char*)glGetString(GL_VERSION));
        AERO_CORE_INFO("Hardware:{0}{1}", (const char*)glGetString(GL_RENDERER), (const char*)glGetString(GL_VERSION));

        glfwWindowHint(GLFW_SAMPLES, 4);

        configCallbacks();

        renderEngine = new Renderer();

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
        renderEngine->draw();
    }

    void GLFWLayer::configCallbacks()
    {
        // Window Event Callback
        //Error callback
        glfwSetErrorCallback(GLFWErrorCallback);


        
        //Resize Callback
        glfwSetWindowSizeCallback(window, [](GLFWwindow* w,int _w, int _h)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(w);
            WindowResizeEvent resize(_w,_h);
            data.EventCallback(resize);

            data.width = _w;
            data.height = _h;
            
            glViewport(0, 0, data.width,data.height);

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

    bool GLFWLayer::onResize(WindowResizeEvent& e)
    {
        glViewport(0, 0, data.width, data.height);

        return true;
    }


    void GLFWLayer::onEvent(Event &event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(GLFWLayer::onResize));

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

        //glfwWindowHint(GLFW_SAMPLES, 4);


    }

}
