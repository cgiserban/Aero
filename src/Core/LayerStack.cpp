#include "LayerStack.h"

namespace Aero
{

    LayerStack::~LayerStack()
    {
        for(Layer* layer : stack)
        {
            layer->onDetach();
            delete layer;
        }
    }

    void LayerStack::pushLayer(Layer* layer)
    {
        stack.emplace(stack.begin() + layerInsertIndex,layer);
        layerInsertIndex++;
    }

    void LayerStack::pushOverlay(Layer* overlay)
    {
        stack.emplace_back(overlay);
    }

    void LayerStack::popLayer(Layer* layer)
    {
        auto it = std::find(stack.begin(),stack.end(),layer);
        if (it != stack.end())
        {
            layer->onDetach();
            stack.erase(it);
            layerInsertIndex--;
        }
    }

    void LayerStack::popOverlay(Layer* overlay)
    {
        auto it = std::find(stack.begin() + layerInsertIndex,stack.end(),overlay);
        if (it != stack.end())
        {
            overlay->onDetach();
            stack.erase(it);
        }

    }
}
