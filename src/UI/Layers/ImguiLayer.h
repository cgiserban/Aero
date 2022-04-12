#pragma once

#include "Core/Layer.h"

#include "UI/Panels/Panel.h"
#include "UI/Panels/NodeEditor.h"
#include "UI/Panels/MenuBar.h"
#include <vector>


namespace Aero
{
    class ImGuiLayer :public Layer
    {
    public:

        ImGuiLayer():Layer("ImguiLayer"){}
        void onAttach() override;
        void onDetach() override;
        void onUpdate() override;
        void onEvent(Event& event) override;
        void renderPanels();

    private:

        bool OnWindowResizeEvent(WindowResizeEvent& e);

    private:
        const char* glsl_version = "#version 130";

        ImGuiViewport* mainViewport;
        ImGuiContext* context;

        NodeEditor* node = new NodeEditor;
        MenuBar* menu = new MenuBar;

        std::vector<Panel*> panelsArray;
        

    };
}
