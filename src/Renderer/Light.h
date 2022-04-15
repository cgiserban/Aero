#pragma once
#include "glm/glm.hpp"

namespace Aero
{
	class Light
	{
	public:
		Light(glm::vec3 _pos, glm::vec4 _color, double _intensity) :pos(_pos), color(_color), intensity(_intensity) {}
		~Light();

		glm::vec3 getPos() { return pos; }
		glm::vec4 getColor() { return color; }
		double getIntensity() { return intensity; }

		const char* getName() { return name; }
		void setName(const char* _name) { name = _name; }

	private:
		glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0);
		glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0);
		double intensity = 1.0;

		const char* name = "Light";

	};
}
