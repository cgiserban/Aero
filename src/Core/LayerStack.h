#pragma once
#include <vector>
#include <algorithm>
#include "Core/Layer.h"

namespace Aero
{
    class LayerStack
    {
    public:

        LayerStack(){};
        ~LayerStack();

        void pushLayer(Layer* layer);
        void popLayer(Layer* layer);

        void pushOverlay(Layer* overlay);
        void popOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin(){return stack.begin();}
        std::vector<Layer*>::iterator end(){return stack.end();}

    private:
        std::vector<Layer*> stack;
        int layerInsertIndex = 0;
    };
}

