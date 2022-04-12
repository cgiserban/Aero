#include "UI.h"

namespace Aero
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    UI* UI::instance = nullptr;

    UI::UI()
    {
        if (instance != nullptr)
        {
            AERO_CORE_ERROR("Program Already Running!");
        }
        instance = this;
        init();

    }

    UI::~UI()
    {
        shutdown();
        for (Layer* layer : uiStack)
        {
            layer->onDetach();
        }
    }

    void UI::init()
    {

        Log::init();

        glfwLayer = new GLFWLayer;
        imguiLayer = new ImGuiLayer;

        pushLayer(glfwLayer);
        glfwLayer->setEventCallback(BIND_EVENT_FN(UI::onEvent));

        pushLayer(imguiLayer);


    }

    void UI::run()
    {

        // Main loop
        while (isRunning)
        {
            for (Layer* layer : uiStack)
            {
                layer->onUpdate();
            }    
            glfwLayer->swapBuffers();
        }

        shutdown();

    }

    void UI::shutdown()
    {
        AERO_CORE_INFO("Shutting down!");
        for (auto it = uiStack.end(); it != uiStack.begin(); )
        {
            (*--it)->onDetach();
        }
    }

    void UI::onEvent(Event &event)
    {

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(UI::onWindowClose)); //If close event is triggered, do close event

        for (auto it = uiStack.end(); it != uiStack.begin(); )
        {
            (*--it)->onEvent(event);
            if (event.handled) break;
        }

        dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(UI::onWindowResize));
    }

    bool UI::onWindowClose(WindowCloseEvent& e)
    {
        isRunning = false;
        return true;
    }

    bool UI::onWindowResize(WindowResizeEvent& e)
    {

        if (e.getWidth() == 0 || e.getHeight() == 0)
        {
            isMinimized = true;
            return true;
        }
        isMinimized = false;
        return false;


    }

    void UI::pushLayer(Layer *layer)
    {
        uiStack.pushLayer(layer);
        layer->onAttach();
    }

    void UI::pushOverlay(Layer *overlay)
    {
        uiStack.pushOverlay(overlay);
        overlay->onAttach();
    }


}
