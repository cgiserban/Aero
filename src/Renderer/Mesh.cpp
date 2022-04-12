#include "Mesh.h"

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

        vao = new VertexArray();

        vbo = new VertexBuffer(vertices, vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);
        vbo->setLayout(layout);
        vao->setVertexBuffer(vbo);

        ibo = new IndexBuffer(indices, indices.size(), GL_STATIC_DRAW);
        vao->unbind();

    }


    void Mesh::Draw(Shader* shader)
    {
        // draw mesh

        vao->bind();
        shader->bind();
        glDrawElements(GL_TRIANGLES, static_cast<uint32_t>(ibo->getCount()), GL_UNSIGNED_INT, 0);
        
        //vao->unbind();

    }

}