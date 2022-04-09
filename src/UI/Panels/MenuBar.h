#pragma once
#include "Panel.h"

namespace Aero
{
    class MenuBar : public Panel
    {
    public:
        MenuBar();
        ~MenuBar();
        void render() override;

    };
}
