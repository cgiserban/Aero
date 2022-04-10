#include "GLFWLayer.h"
#include "UI/UI.h"
#include "UI/Event/ApplicationEvent.h"

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

        configCallbacks();
        drawInit();
    }

    void GLFWLayer::onDetach()
    {

        glfwWindowShouldClose(window);
        glfwDestroyWindow(window);
        glfwTerminate();

    }


    void GLFWLayer::drawInit()
    {
        // Vertex Array
        // Vertex Buffer
        // Index Buffer
        
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

        float vertices[3 * 3] =
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f, 0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

        unsigned int indices[3] = { 0,1,2 };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        /*

        glm::mat4 M = glm::mat4();
        glm::mat4 V = glm::lookAt(glm::vec3(0,1,0),glm::vec3(0,0,0),glm::vec3(0,1,0));
        glm::mat4 P = glm::ortho(-6400,6400,6400,-6400);

        glm::mat4 MVP = M * V * P;
        */

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position,1.0);
            }

        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 v_Position;
            void main()
            {
                color = vec4(v_Position*0.5 + 0.5,1.0);
            }
        )";

        testShader.reset(new Shader(vertexSrc, fragmentSrc));
        testShader->bind();




    }


    void GLFWLayer::onUpdate()
    {
        glfwPollEvents();

        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        glClear(GL_COLOR_BUFFER_BIT);

        
        glBindVertexArray(vertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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



    }

}
