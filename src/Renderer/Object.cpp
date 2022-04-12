#include "Object.h"

namespace Aero 
{
    Object::Object(std::string& path)
    {
        loadModel(path);
    }


    void Object::loadModel(std::string& path)
    {
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            AERO_CLIENT_ERROR("{0}", import.GetErrorString());
        }

        processNode(scene->mRootNode, scene);

    }

    void Object::processNode(aiNode* node, const aiScene* scene)
    {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }

    }

    Mesh Object::processMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            // process vertex positions, normals and texture coordinates
            glm::vec3 vp, vn;
            vp.x = mesh->mVertices[i].x;
            vp.y = mesh->mVertices[i].y;
            vp.z = mesh->mVertices[i].z;
            vertex.Position = vp;


            vn.x = mesh->mNormals[i].x;
            vn.y = mesh->mNormals[i].y;
            vn.z = mesh->mNormals[i].z;
            vertex.Normal = vn;

            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords= vec;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }

        // process indices

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }


        // process material
        if (mesh->mMaterialIndex >= 0)
        {
            /*
            if (mesh->mMaterialIndex >= 0)
            {

                aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
                vector<Texture> diffuseMaps = loadMaterialTextures(material,
                    aiTextureType_DIFFUSE, "texture_diffuse");
                textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
                vector<Texture> specularMaps = loadMaterialTextures(material,
                    aiTextureType_SPECULAR, "texture_specular");
                textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

            }
            */

        }

        return Mesh(vertices, indices);//, textures);
    }

    void Object::draw(Shader* shader)
    {
        for (int i = 0; i < meshes.size(); i++)
        {
            meshes[i].setShader(shader);
            meshes[i].Draw(shader);
        }
    }

}