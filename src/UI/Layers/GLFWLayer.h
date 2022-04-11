#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core/Layer.h"
#include "Core/Window.h"

#include "Renderer/Renderer.h"


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

        void configCallbacks();
        void update(){ glfwSwapBuffers(window); }

        GLFWwindow* get(){return window;}

        using EventCallbackFn = std::function<void(Event&)>;
        void setEventCallback(const EventCallbackFn& callback){data.EventCallback = callback;};

        WindowData data;


    private:

        bool onResize(WindowResizeEvent& e);

        Renderer* renderEngine;
        bool isRunning = true;
        GLFWwindow* window;
        WindowProps props;

    };
}
