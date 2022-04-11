#include "Camera.h"

namespace Aero
{

	Camera::Camera()
	{
		setDefault();
		update();
	}

	Camera::Camera(glm::vec3 _eye, glm::vec3 _look, glm::vec3 _up,
				   float _fov, float _aspectRatio, float _near, float _far)
	{
		pos = _eye;
		look = _look;
		u = _up;
		fov = _fov;
		aspectRatio = _aspectRatio;
		clipNear = _near;
		clipFar = _far;
		
		viewMatrix = glm::lookAt(pos, look, u);
		projectionMatrix = glm::perspective(glm::degrees(fov), aspectRatio, clipNear, clipFar);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
		
		update();

	}

	void Camera::setDefault()
	{
		fov = 46;
		aspectRatio = 1.77;
		clipFar = 1000;
		clipNear = 0.001;
		
		pos = glm::vec3(0.0, 0.0, 1.0);
		look = glm::vec3(0.0, 0.0, 0.0);
		up = glm::vec3(0.0, 1.0, 0.0);

		update();

	}

	void Camera::update()
	{
		dir = glm::normalize(pos - look);
		r = glm::normalize(glm::cross(u, dir));
		up = glm::normalize(glm::cross(r, dir));

		viewMatrix = glm::lookAt(pos, look, u);
		projectionMatrix = glm::perspective(glm::degrees(fov), aspectRatio, clipNear, clipFar);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
		
	}

	void Camera::move(glm::vec3 m)
	{
		pos = pos + m;
		look = look + m;
		update();
	}

	void Camera::dolly(float s)
	{
		update();
	}

	void Camera::zoom(float s)
	{
		update();
	}

}