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
		void draw(Shader* shader);
		void unbind();

	private:
		std::vector<Mesh> meshes;

	};
}
