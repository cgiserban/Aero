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

        vbo = new VertexBuffer(vertices, sizeof(vertices),GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        uint32_t indices[3] = { 0,1,2 };
        ibo = new IndexBuffer(indices, sizeof(indices) / sizeof(uint32_t), GL_DYNAMIC_DRAW);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec4 pos;
            uniform mat4 MVP;
            out vec3 v_Position;

            void main()
            {
                v_Position = pos.rgb;
                gl_Position = MVP * pos;
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

        cam = new Camera(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
                         54.0, 1.77, 0.00001, 100000);


	}
    void Renderer::draw()
    {


        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 M = glm::mat4(1.0f);        
        glm::mat4 MVP = cam->viewProjection() * M;

        unsigned int location = glGetUniformLocation(shader->get(), "MVP");
        glUniformMatrix4fv(location, 1, GL_FALSE, &MVP[0][0]);
        
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, nullptr);



    }
}
