#include "Renderer.h"
#include "UI/UI.h"

namespace Aero 
{
	void Renderer::init()
	{
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        
        defaultScene = new Scene();

	}

    void Renderer::render()
    {
        clear();

        defaultScene->render();

    }

    void Renderer::clear()
    {

        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    }
}
