#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core/Layer.h"
#include "Core/Window.h"

#include "Renderer/Renderer.h"
#include <iostream>

namespace Aero
{
    class GLFWLayer : public Layer,public Window
    {
    public:
        GLFWLayer();

        void onAttach() override;
        void onDetach() override;
        void onUpdate() override;
        void onEvent(Event& event) override;

        unsigned int getWidth() override;
        unsigned int getHeight() override;


        void configCallbacks();
        void pollEvents() { glfwPollEvents(); }// glfwSwapBuffers(window); }
        void swapBuffers() { glfwSwapBuffers(window); }// glfwSwapBuffers(window); }

        GLFWwindow* get(){return window;}

        using EventCallbackFn = std::function<void(Event&)>;
        void setEventCallback(const EventCallbackFn& callback){data.EventCallback = callback;};

        WindowData data;


    private:

        bool OnWindowResizeEvent(WindowResizeEvent& e);

        Renderer* renderEngine;
        bool isRunning = true;
        GLFWwindow* window;
        WindowProps props;

    };
}
