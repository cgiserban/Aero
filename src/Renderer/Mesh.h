#pragma once

#include "Buffer.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

namespace Aero
{


    class Mesh {
    public:

        Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);

        void draw(Shader* shader);

        void bind() { vao->bind(); }

        void unbind()
        {
            vao->unbind();
            vbo->unbind();
            ibo->unbind();
        }

        void setShader(Shader* s) { s->bind(); }
        Shader* getShader() { return shader; }


    private:


        VertexArray* vao;
        VertexBuffer* vbo;
        IndexBuffer* ibo;

        Shader* shader;


    };
}
