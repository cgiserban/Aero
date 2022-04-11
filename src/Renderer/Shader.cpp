#include "Shader.h"

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

	void Shader::setUniformf(float f, const char* name)
	{
		unsigned int location = glGetUniformLocation(rendererID, name);
		glUniform1f(location, f);
	}

	void Shader::setUniformi(int i, const char* name)
	{
		unsigned int location = glGetUniformLocation(rendererID, name);
		glUniform1i(location, i);
	}

	void Shader::setUniform3f(glm::vec3 vect, const char* name)
	{
		unsigned int location = glGetUniformLocation(rendererID, name);
		glUniform3f(location, vect.x, vect.y, vect.z);
	}

	void Shader::setUniform4f(glm::vec4 vect, const char* name)
	{
		unsigned int location = glGetUniformLocation(rendererID, name);
		glUniform4f(location, vect.r, vect.g, vect.b, vect.a);
	}

	void Shader::setUniformM4f(glm::mat4 matrix, const char* name)
	{
		unsigned int location = glGetUniformLocation(rendererID, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}



}