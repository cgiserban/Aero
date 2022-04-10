#include "Renderer.h"
namespace Aero 
{
	void Renderer::init()
	{
        float vertices[3 * 3] =
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f, 0.5f, 0.0f
        };

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        vbo = new VertexBuffer(vertices, sizeof(vertices));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        uint32_t indices[3] = { 0,1,2 };
        ibo = new IndexBuffer(indices, sizeof(indices) / sizeof(uint32_t));

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position,1.0);
            }

        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 v_Position;
            void main()
            {
                color = vec4(v_Position*0.5 + 0.5,1.0);
            }
        )";

        shader = new Shader(vertexSrc, fragmentSrc);
        shader->bind();

        /*

        glm::mat4 M = glm::mat4();
        glm::mat4 V = glm::lookAt(glm::vec3(0,1,0),glm::vec3(0,0,0),glm::vec3(0,1,0));
        glm::mat4 P = glm::ortho(-6400,6400,6400,-6400);

        glm::mat4 MVP = M * V * P;
*/

	}
    void Renderer::draw()
    {


        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        glClear(GL_COLOR_BUFFER_BIT);


        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, nullptr);



    }
}
