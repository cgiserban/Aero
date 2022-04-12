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


		void loadModel(std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);


		void draw(Shader* shader);
		void unbind();

	private:
		std::vector<Mesh> meshes;

	};

}
