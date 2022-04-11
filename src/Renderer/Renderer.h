#pragma once

#include "Renderer/Shader.h"
#include "Camera.h"
#include "Renderer/Buffer.h"

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

	private:

		unsigned int vao;
		glm::vec4 bgColor = glm::vec4(0.18, 0.18, 0.18, 1.0);

		VertexBuffer* vbo;
		IndexBuffer* ibo;
		Shader* shader;
		Camera* cam;

	};
}
