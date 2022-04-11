#pragma once

#include "glm/glm.hpp"
//#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
namespace Aero {

	class Camera
	{
	public:
		Camera();

		Camera(glm::vec3 _eye, glm::vec3 _look, glm::vec3 _up,
			   float _fov=45.0, float _aspectRatio = 1.77, float _near = 0.01, float _far = 100.0);

		
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

		float clipNear;
		float clipFar;

		float fov;
		float aspectRatio;

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
