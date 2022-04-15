#pragma once

#include <GL/glew.h>
#include "Core/Log.h"
#include <sstream>
#include <fstream>
#include <string>

#include "glm/glm.hpp"

namespace Aero
{

	struct TextureData
	{
		TextureData(int _location,const char* _name, const char* _path):
			location(_location),name(_name),path(_path){}

		int location;
		const char* name;
		const char* path;
	};

	class Shader
	{
	public:
		Shader(const std::string& vs, const std::string& fs);
		~Shader();

		static std::string ParseShader(const std::string& filePath);


		void bind() { glUseProgram(rendererID); }
		void unbind() { glUseProgram(0); }
		uint32_t get() { return rendererID; }

		//Uniforms
		void setUniformf(float f, const char* name);
		void setUniformi(int i, const char* name);
		void setUniform3f(glm::vec3 vect, const char* name);
		void setUniform4f(glm::vec4 vect, const char* name);
		void setUniformM4f(glm::mat4 matrix, const char* name);

		//Textures
		void setTexture(int location,const char* name, std::string texPath, bool mipMapped = true);
		void listTextures();


	private:
		uint32_t rendererID;
		std::vector<TextureData> textures;

		

	};
}
