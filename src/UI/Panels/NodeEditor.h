#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Panel.h"

namespace Aero
{
    class NodeEditor : public Panel
    {
    public:
        NodeEditor();
        NodeEditor(GLFWwindow* _parent);
        ~NodeEditor();
        void render() override;
    private:
        int uid = 0;
    };
}
