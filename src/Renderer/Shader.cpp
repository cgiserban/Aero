#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Aero
{

	Shader::Shader(const std::string& vs, const std::string& fs)
	{

		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vs.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			AERO_CORE_ERROR("Vertex Shader Compilation Error:");
			AERO_CORE_ERROR("{0}", infoLog.data());

			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fs.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			AERO_CORE_ERROR("Fragment Shader Compilation Error:");
			AERO_CORE_ERROR("{0}", infoLog.data());

			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		rendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(rendererID, vertexShader);
		glAttachShader(rendererID, fragmentShader);

		// Link our program
		glLinkProgram(rendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(rendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(rendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(rendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(rendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			AERO_CORE_ERROR("Shader Link Compilation Error:");
			AERO_CORE_ERROR("{0}", infoLog.data());

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(rendererID, vertexShader);
		glDetachShader(rendererID, fragmentShader);

	}

	Shader::~Shader()
	{
		glDeleteProgram(rendererID);
	}

	std::string Shader::ParseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		std::string line;

		std::stringstream ss;
	
		while (getline(stream, line))
		{
			ss << line << '\n';
		}

		return ss.str();

	}

	void Shader::setUniformf(float f, const char* name)
	{
		this->bind();
		unsigned int location = glGetUniformLocation(rendererID, name);
		glUniform1f(location, f);
		this->unbind();

	}

	void Shader::setUniformi(int i, const char* name)
	{
		this->bind();
		unsigned int location = glGetUniformLocation(rendererID, name);
		glUniform1i(location, i);
		this->unbind();

	}

	void Shader::setUniform3f(glm::vec3 vect, const char* name)
	{
		this->bind();
		unsigned int location = glGetUniformLocation(rendererID, name);
		glUniform3f(location, vect.x, vect.y, vect.z);
		this->unbind();
	}

	void Shader::setUniform4f(glm::vec4 vect, const char* name)
	{
		this->bind();
		unsigned int location = glGetUniformLocation(rendererID, name);
		glUniform4f(location, vect.r, vect.g, vect.b, vect.a);
		this->unbind();

	}

	void Shader::setUniformM4f(glm::mat4 matrix, const char* name)
	{
		this->bind();
		unsigned int location = glGetUniformLocation(rendererID, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
		this->unbind();

	}

	void Shader::setTexture(int location, const char* name, std::string texturePath, bool mipMapped)
	{

		const char* texPath = texturePath.c_str();
		std::string extension = texturePath.substr(texturePath.find_last_of(".") + 1);
		
		unsigned int texID;
		glCreateTextures(GL_TEXTURE_2D, 1, &texID);

		glActiveTexture(GL_TEXTURE0+location);
		glBindTexture(GL_TEXTURE_2D, texID);

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


		glTextureStorage2D(texID, 1, GL_RGB16, w, h);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
		
		if (data)
		{
			if (extension == "jpg" || extension == "tga")
			{
				glTextureSubImage2D(texID, 0, 0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);
				textures.push_back(TextureData(location, name, texPath));
				setUniformi(location, name);
				stbi_image_free(data);

			}
			else if (extension == "png")
			{
				glTextureSubImage2D(texID, 0, 0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
				textures.push_back(TextureData(location, name, texPath));
				setUniformi(location, name);
				stbi_image_free(data);
			}
		else
			{
				AERO_CORE_ERROR("Texture {0} could not be loaded", texPath);
			}
		}
	}




	void Shader::listTextures()
	{
		AERO_CORE_TRACE("SHADER TEXTURES");

		AERO_CORE_TRACE("------------------------------------------------------");
		for (int i = 0; i < textures.size(); i++)
		{
			AERO_CORE_INFO("Index {0}: {1} -> {2}", textures[i].location,textures[i].name, textures[i].path);
		}
		AERO_CORE_TRACE("------------------------------------------------------");

	}


}