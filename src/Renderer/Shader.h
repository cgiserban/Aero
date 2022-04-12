#pragma once

#include <GL/glew.h>
#include "Core/Log.h"
#include "glm/glm.hpp"
#include <sstream>
#include <fstream>
#include <string>

namespace Aero
{
	class Shader
	{
	public:
		Shader(const std::string& vs, const std::string& fs);
		~Shader();

		static std::string ParseShader(const std::string& filePath);


		void bind() { glUseProgram(rendererID); }
		void unbind() { glUseProgram(0); }
		uint32_t get() { return rendererID; }

		void setUniformf(float f, const char* name);
		void setUniformi(int i, const char* name);
		void setUniform3f(glm::vec3 vect, const char* name);
		void setUniform4f(glm::vec4 vect, const char* name);
		void setUniformM4f(glm::mat4 matrix, const char* name);

	private:
		uint32_t rendererID;

		

	};
}
