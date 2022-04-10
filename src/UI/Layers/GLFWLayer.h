#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include "Core/Layer.h"
#include "Core/Window.h"
#include "glm/vec4.hpp"

#include "Renderer/Shader.h"

namespace Aero
{
    class GLFWLayer : public Layer,public Window
    {
    public:
        GLFWLayer():Layer("GLFWLayer"), Window(WindowProps()){}



        void onAttach() override;
        void onDetach() override;
        void onUpdate() override;
        void onEvent(Event& event) override;
        void setVSync(bool enabled) override;

        static void init();
        void drawInit();

        void configCallbacks();
        void update(){glfwSwapBuffers(window);}

        GLFWwindow* get(){return window;}

        using EventCallbackFn = std::function<void(Event&)>;
        void setEventCallback(const EventCallbackFn& callback){data.EventCallback = callback;};

        WindowData data;

        unsigned int vertexArray, vertexBuffer, indexBuffer;
        glm::vec4 bgColor=glm::vec4(0.18,0.18,0.18,1.0);

    private:



        bool onResize(WindowResizeEvent& e);


        bool isRunning = true;
        GLFWwindow* window;
        WindowProps props;

        std::unique_ptr<Shader> testShader;

    };
}
