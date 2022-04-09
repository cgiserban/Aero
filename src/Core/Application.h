#pragma once
#include "UI/UI.h"

namespace Aero
{
    class Application
    {
    public:
        Application(){};
        ~Application(){}

        void run();

    private:
        UI appUI;

    }; 


}
