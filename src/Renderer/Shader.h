#pragma once

#include <GL/glew.h>
#include "Core/Log.h"


namespace Aero
{
	class Shader
	{
	public:
		Shader(const std::string& vs, const std::string& fs);
		~Shader();


		void bind() { glUseProgram(rendererID); }
		void unbind() { glUseProgram(0); }


	private:
		uint32_t rendererID;

		

	};
}
