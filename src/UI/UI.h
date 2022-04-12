#pragma once 

#include <Windows.h>

#include "Layers/GLFWLayer.h"
#include "Layers/ImguiLayer.h"

#include "Core/LayerStack.h"
#include "Core/Log.h"


namespace Aero
{
    class UI
    {
    
    public:
        UI();
        ~UI();

        void init();
        void run();
        void shutdown();

        void onEvent(Event& event);
        bool onWindowClose(WindowCloseEvent& e);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);

        static UI& getInstance() {return *instance;}
        GLFWwindow* getWindow() {return glfwLayer->get();}
        
        unsigned int getWidth(){return glfwLayer->getHeight();}
        unsigned int getHeight(){return glfwLayer->getWidth();}

    private:

        static UI* instance;

        bool isRunning = true;

        LayerStack uiStack;
        ImGuiLayer* imguiLayer;
        GLFWLayer* glfwLayer;

    };

}
