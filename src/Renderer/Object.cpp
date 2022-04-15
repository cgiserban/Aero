#include "Object.h"

namespace Aero 
{
    Object::Object(std::string path)
    {
        
        loadModel(path);
    }

    Object::Object(Object* obj)
    {
        meshes = obj->getMeshes();
    }


    void Object::loadModel(std::string& path)
    {
        //Loading Scene
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            AERO_CLIENT_ERROR("{0}", import.GetErrorString());
        }

        if (scene != NULL) processNode(scene->mRootNode, scene);
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

    Object Object::createPrimTriangle()
    {
        Vertex v1(glm::vec3( 0.0, 0.0, 0.0), glm::vec3(0.5, 0.5, 1.0), glm::vec2(0.0, 0.0));
        Vertex v2(glm::vec3( 1.0, 0.0, 0.0), glm::vec3(0.5, 0.5, 1.0), glm::vec2(1.0, 0.0));
        Vertex v3(glm::vec3( 0.0, 1.0, 0.0), glm::vec3(0.5, 0.5, 1.0), glm::vec2(0.5, 1.0));

        std::vector<Vertex> vertices;
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);

        std::vector<uint32_t> indices;
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);


        Object obj;
        obj.addMesh(Mesh(vertices,indices));

        return obj;
    }

    Object Object::createPrimSquare()
    {
        Vertex v1(glm::vec3(-0.5, -0.5, 0.0), glm::vec3(0.5, 0.5, 1.0), glm::vec2(0.0, 0.0));
        Vertex v2(glm::vec3(0.5, -0.5, 0.0), glm::vec3(0.5, 0.5, 1.0), glm::vec2(1.0, 0.0));
        Vertex v3(glm::vec3(0.5, 0.5, 0.0), glm::vec3(0.5, 0.5, 1.0), glm::vec2(1.0, 1.0));
        Vertex v4(glm::vec3(-0.5, 0.5, 0.0), glm::vec3(0.5, 0.5, 1.0), glm::vec2(0.0, 1.0));

        std::vector<Vertex> vertices;
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        vertices.push_back(v4);

        std::vector<uint32_t> indices;
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);

        indices.push_back(2);
        indices.push_back(3);
        indices.push_back(0);


        Object obj;
        obj.addMesh(Mesh(vertices, indices));
        return obj;
    }



    Object Object::createPrimRectangle()
    {
        Vertex v1(glm::vec3(-0.5,-0.25, 0.0), glm::vec3(0.5, 0.5, 1.0), glm::vec2(0.0, 0.0));
        Vertex v2(glm::vec3( 0.5,-0.25, 0.0), glm::vec3(0.5, 0.5, 1.0), glm::vec2(1.0, 0.0));
        Vertex v3(glm::vec3( 0.5, 0.25, 0.0),  glm::vec3(0.5, 0.5, 1.0), glm::vec2(1.0, 1.0));
        Vertex v4(glm::vec3(-0.5, 0.25, 0.0),  glm::vec3(0.5, 0.5, 1.0), glm::vec2(0.0, 1.0));

        std::vector<Vertex> vertices;
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        vertices.push_back(v4);

        std::vector<uint32_t> indices;
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(2);

        indices.push_back(2);
        indices.push_back(3);
        indices.push_back(0);


        Object obj;
        obj.addMesh(Mesh(vertices, indices));
        return obj;
    }


    void Object::addMesh(Mesh m)
    {
        meshes.push_back(m);
    }

    void Object::draw(Shader* shader)
    {
        for (int i = 0; i < meshes.size(); i++)
        {
            meshes[i].bind();
            meshes[i].setShader(shader);
            meshes[i].draw(shader);
        }
    }

    void Object::unbind()
    {
        for (int i = 0; i < meshes.size(); i++)
        {
            meshes[i].unbind();
        }
    }

}