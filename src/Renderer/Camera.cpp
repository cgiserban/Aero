#include "Camera.h"

namespace Aero
{

	Camera::Camera()
	{
		setDefault();
		update();
	}

	Camera::Camera(glm::vec3 _eye, glm::vec3 _look, glm::vec3 _up,
				   double _fov, double _aspectRatio, double _near, double _far)
	{
		pos = _eye;
		look = _look;
		up = _up;
		fov = _fov;
		aspectRatio = _aspectRatio;
		clipNear = _near;
		clipFar = _far;
		
		viewMatrix = glm::lookAt(pos, look, up);
		projectionMatrix = glm::perspective(fov, aspectRatio, clipNear, clipFar);
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
		//r = glm::normalize(glm::cross(up, dir));
		//u = glm::normalize(glm::cross(r, dir));

		viewMatrix = glm::lookAt(pos, look, up);
		projectionMatrix = glm::perspective(fov, aspectRatio, clipNear, clipFar);
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