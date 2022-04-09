#pragma once

#include "UI/Event/Event.h"
#include "UI/Event/ApplicationEvent.h"
#include "UI/Event/KeyEvent.h"
#include "UI/Event/MouseEvent.h"


namespace Aero
{
    class Layer
    {
    public:
        Layer( const char* _name = "Layer"): name(_name) {};
        virtual ~Layer(){};

        virtual void onAttach(){}
        virtual void onDetach(){}
        virtual void onUpdate(){}
        virtual void onEvent(Event& event){}

        const char* getName() const{ return name;}

    private:
        const char* name = "Layer";
        bool isEnabled = true;
    };
}
