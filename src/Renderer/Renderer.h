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
		Shader* shader2;

		Camera* cam;
		Object* obj;
		Object* obj2;

		glm::mat4 M;
		glm::mat4 V;
		glm::mat4 P;

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

	};
}
