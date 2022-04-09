#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Aero
{
    class Panel
    {
    public:
        virtual void render() = 0;
        ImGuiIO io;
    };
}
