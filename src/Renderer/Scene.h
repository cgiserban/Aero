#pragma once

#include "Renderer/Shader.h"
#include "Renderer/Camera.h"
#include "Renderer/Buffer.h"
#include "Renderer/Object.h"
#include "Renderer/Texture.h"
#include "Renderer/Light.h"

#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtx/transform.hpp"

namespace Aero
{
	
	/*
	template <typename T>
	T getEntity(const char* name,std::vector<T> vect)
	{
		for (int i = 0; i < vect.size(); i++)
		{
			if (vect[i].getName() == name)
			{
				return vect[i];
			}
		}
	}
	*/
	

	class Scene
	{
	public:
		Scene() { createScene(); }
		~Scene() {}

		void createScene();
		void render();
		



		/*
		void addShader(Shader* shader)	{shaders.push_back(shader);}
		void addObject(Object* object)	{objects.push_back(object);}
		void addTexture(Texture* texture){textures.push_back(texture);}
		void addLight(Light* light)		{lights.push_back(light);}
		void addCamera(Camera* camera)	{cameras.push_back(camera);}
		*/

	private:


		Shader* mainShader;
		Shader* constantShader;
		Texture* diffColor;
		Object* teapot;
		Light* pointLight;
		Camera* defaultCam;

		float angle = 0.0;

		/*
		std::vector<Shader*> shaders;
		std::vector<Texture*> textures;
		std::vector<Camera*> cameras;
		std::vector<Object*> objects;
		std::vector<Light*> lights;
		*/
		
	};

}