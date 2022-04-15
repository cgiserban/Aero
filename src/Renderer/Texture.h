#pragma once

#include <GL/glew.h>

#include "Core/Log.h"

#include <sstream>
#include <fstream>
#include <string>



namespace Aero
{
	class Texture
	{
	public:
		Texture(std::string path);
		~Texture();

		void create(std::string path);
		uint32_t get() { return textureID; }
		const char* getPath() { return texturePath.c_str(); }

		const char* getName() { return name; }
		void setName(const char* _name) { name = _name; }


	private:
		uint32_t textureID;
		std::string texturePath;
		const char* name = "Texture";
	};
}
