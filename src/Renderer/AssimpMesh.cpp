#include "AssimpMesh.h"

namespace Aero 
{
    // constructor

    Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<uint32_t> _indices)
    {

        this->vertices = _vertices;
        this->indices = _indices;

        BufferLayout layout =
        {
            {ShaderDataType::Float3, "pos"},
            {ShaderDataType::Float3, "normal"},
            {ShaderDataType::Float2, "texCoords"}
        };

        vbo = new VertexBuffer(vertices, vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);
        vbo->setLayout(layout);

        ibo = new IndexBuffer(indices, indices.size(), GL_STATIC_DRAW);

        vao = new VertexArray(vbo, ibo);


    }


    void Mesh::Draw(Shader* shader)
    {
        // draw mesh

        vao->bind();
        glDrawElements(GL_TRIANGLES, static_cast<uint32_t>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

    }

}