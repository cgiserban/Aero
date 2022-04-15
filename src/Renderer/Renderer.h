#pragma once

#include "Renderer/Scene.h"

#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtx/transform.hpp"


namespace Aero
{
	class Renderer
	{
	public:
		Renderer() {init();}
		~Renderer() {}

		void init();
		void render();
		void clear();

	private:

		glm::vec4 bgColor = glm::vec4(0.18, 0.18, 0.18, 1.0);

		Scene* defaultScene;

	};
}
