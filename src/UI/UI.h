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
        bool onWindowResize(WindowResizeEvent& e);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);

        static UI& getInstance() {return *instance;}
        bool isWindowMimimized() { return isMinimized; }
        GLFWwindow* getWindow() {return glfwLayer->get();}
        
        unsigned int getWidth(){return glfwLayer->getWidth();}
        unsigned int getHeight(){return glfwLayer->getHeight();}

    private:

        static UI* instance;

        bool isRunning = true;
        bool isMinimized = false;
        
        LayerStack uiStack;
        ImGuiLayer* imguiLayer;
        GLFWLayer* glfwLayer;

    };

}
