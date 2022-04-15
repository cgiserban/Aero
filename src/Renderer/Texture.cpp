#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Aero
{
	Texture::Texture(std::string path)
	{
		create(path);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &textureID);
	}

	void Texture::create(std::string path)
	{

		texturePath = path;
		const char* texPath = path.c_str();
		std::string extension = path.substr(path.find_last_of(".") + 1);

		glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		int w, h, nrChannels;
		stbi_set_flip_vertically_on_load(1);

		unsigned char* data = nullptr;


		if (extension == "jpg" || extension == "tga")
		{
			data = stbi_load(texPath, &w, &h, &nrChannels, STBI_rgb);
		}
		else if (extension == "png")
		{
			data = stbi_load(texPath, &w, &h, &nrChannels, STBI_rgb_alpha);
		}


		glTextureStorage2D(textureID, 1, GL_RGB16, w, h);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

		if (data)
		{
			if (extension == "jpg" || extension == "tga")
			{
				glTextureSubImage2D(textureID, 0, 0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);

			}
			else if (extension == "png")
			{
				glTextureSubImage2D(textureID, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				AERO_CORE_ERROR("Texture {0} could not be loaded", texPath);
			}
		}
	}
}