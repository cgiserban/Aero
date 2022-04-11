#include "ImguiLayer.h"
#include "UI/UI.h"

namespace Aero
{
    #define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    void ImGuiLayer::onAttach()
    {

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        context = ImGui::CreateContext();
        ImGui::StyleColorsDark();   // Setup Dear ImGui style

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

        UI& ui = UI::getInstance();
        ImGui_ImplGlfw_InitForOpenGL(ui.getWindow(), true);
        ImGui_ImplOpenGL3_Init(glsl_version);


        panelsArray.push_back(node);
        //panelsArray.push_back(menu);
    }


    void ImGuiLayer::onUpdate()
    {

        ImGui::SetCurrentContext(context);

        UI& ui = UI::getInstance();

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(ui.getWidth(), ui.getHeight());

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        //Docking
        mainViewport = ImGui::GetMainViewport();
        ImGui::DockSpaceOverViewport(mainViewport, ImGuiDockNodeFlags_NoSplit | ImGuiDockNodeFlags_PassthruCentralNode);

        renderPanels();
        ImGui::ShowDemoWindow();

        //ImGui Render
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }


    }

    void ImGuiLayer::onEvent(Event &event)
    {
        EventDispatcher Dispatcher(event);
        Dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));

    }


    void ImGuiLayer::onDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

    }


    void ImGuiLayer::renderPanels()
    {
        if(panelsArray.size()!=0)
        {
            for(int i = 0; i<(int)panelsArray.size(); i++)
            {
                panelsArray[i]->render();
            }
        }
    }
    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {

        UI& ui = UI::getInstance();
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(ui.getWidth(), ui.getHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, ui.getWidth(), ui.getHeight());
      
        return true;
    }
}
