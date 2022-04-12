#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
namespace Aero {

	class Camera
	{
	public:
		Camera();

		Camera(glm::vec3 _eye, glm::vec3 _look, glm::vec3 _up,
			double _fov=45.0, double _aspectRatio = 1.77, double _near = 0.0001, double _far = 500.0);

		
		void move(glm::vec3 m);
		void rotate(glm::vec3 r) {};
		void dolly(float s);
		void zoom(float s);

		void setDefault();
		void update();

		glm::mat4 view() { return viewMatrix; }
		glm::mat4 projection() { return projectionMatrix; }
		glm::mat4 viewProjection() { return viewProjectionMatrix; }

	//private:

		double clipNear;
		double clipFar;

		double fov;
		double aspectRatio;

		glm::vec3 pos; //Camera Pos
		glm::vec3 look; //Camera Target
		glm::vec3 up; //Camera Up
		
		glm::vec3 u; //Worldspace Up
		glm::vec3 r; //Camera Right

		glm::vec3 dir;

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::mat4 viewProjectionMatrix;

	};
}
