#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Renderer/Mesh.h"

namespace Aero
{
	class Object
	{
	public:
		Object(std::string path);
		Object() {};
		Object(Object* obj);

		void loadModel(std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);

		static Object createPrimTriangle();
		static Object createPrimSquare();
		static Object createPrimRectangle();


		std::vector<Mesh> getMeshes() { return meshes; }
		void addMesh(Mesh m);
	
		Shader* getShader() { return attachedShader; }
		void addShader(Shader* shader) { attachedShader = shader; }

		void draw();
		void unbind();

		const char* getName() { return name; }
		void setName(const char* _name) { name = _name; }

	private:
		std::vector<Mesh> meshes;
		Shader* attachedShader;
		const char* name = "Object";
	};
}
