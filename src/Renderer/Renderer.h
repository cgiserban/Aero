#pragma once

#include "Renderer/Shader.h"
#include "Renderer/Camera.h"
#include "Renderer/Buffer.h"
#include "Renderer/Object.h"

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
		void draw();
		void clear();

	private:

		glm::vec4 bgColor = glm::vec4(0.18, 0.18, 0.18, 1.0);
		float angle = 0;


		Shader* shader;

		Camera* cam;
		Object* obj;



	};
}
