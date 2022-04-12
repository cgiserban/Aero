#include "UI/UI.h"
#include "GLFWLayer.h"


namespace Aero
{
    #define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)


    static void GLFWErrorCallback(int err, const char* desc)
    {
        AERO_CORE_ERROR("GLFW Error: ({0}): {1})", err, desc);
    }


    GLFWLayer::GLFWLayer() : Layer("GLFWLayer"), Window(WindowProps()) 
    {
        if (!glfwInit())
            AERO_CORE_ERROR("Failed Initializing GLFW!");
    
        glfwWindowHint(GLFW_SAMPLES, 8);

    }

    void GLFWLayer::onAttach()
    {
        

        window = glfwCreateWindow(props.width,props.height,props.title,nullptr,nullptr);
        
        glfwMakeContextCurrent(window);
        
        glfwSwapInterval(1); // VSync
        glfwSetWindowUserPointer(window,&data);

        glfwSetWindowAspectRatio(window, props.width, props.height);
        

        if (glewInit() != GLEW_OK)
            AERO_CORE_ERROR("Failed Initializing GLEW!");

        AERO_CORE_INFO("OpenGL:{0}", (const char*)glGetString(GL_VERSION));
        AERO_CORE_INFO("Hardware:{0}{1}", (const char*)glGetString(GL_RENDERER), (const char*)glGetString(GL_VERSION));

        configCallbacks();
        renderEngine = new Renderer();

    }


    void GLFWLayer::onUpdate()
    {
        UI& ui = UI::getInstance();

        glfwPollEvents();
        
        if (!ui.isWindowMimimized())
        {
            renderEngine->draw();
        }
    }


    void GLFWLayer::onDetach()
    {
        glfwWindowShouldClose(window);
        glfwDestroyWindow(window);
        glfwTerminate();
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
           

            data.width = _w;
            data.height = _h;

            WindowResizeEvent event(_w, _h);
            data.EventCallback(event);


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

    bool GLFWLayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {

        glViewport(0, 0, e.getWidth(), e.getHeight());

        return true;
    }


    void GLFWLayer::onEvent(Event &event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(GLFWLayer::OnWindowResizeEvent));

    }

    unsigned int GLFWLayer::getWidth()
    {
        return data.width;
    }

    unsigned int GLFWLayer::getHeight()
    {
        return data.height;
    }

}
