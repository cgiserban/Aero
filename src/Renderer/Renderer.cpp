#include "Renderer.h"

namespace Aero 
{
	void Renderer::init()
	{
        float vertices[3 * 3 + 3 * 4] =
        {
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f,     0.0f, 1.0f, 1.0f, 1.0f
        };

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        vbo = new VertexBuffer(vertices, sizeof(vertices),GL_DYNAMIC_DRAW);

        {
            BufferLayout layout =
            {
                {ShaderDataType::Float3, "pos"},
                {ShaderDataType::Float4, "colorPassed"}
            };

            vbo->setLayout(layout);
        }



        uint32_t elemindex = 0;
        for (const auto& element : vbo->getLayout())
        {
            glEnableVertexAttribArray(elemindex);
            glVertexAttribPointer(elemindex, element.getElementCount(), ShaderDataTypeToOpenGL(element.type),
                                  GL_FALSE, vbo->getLayout().getStride(),(const void*)element.offset);
            elemindex++;
        }

        uint32_t indices[3] = { 0,1,2 };
        ibo = new IndexBuffer(indices, sizeof(indices) / sizeof(uint32_t), GL_DYNAMIC_DRAW);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec4 pos;
            layout(location = 1) in vec4 colorPassed;

            uniform mat4 MVP;
            out vec4 v_Color;

            void main()
            {
                v_Color = colorPassed;
                gl_Position = MVP * pos;
            }

        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec4 v_Color;
            void main()
            {
                color = v_Color;
            }
        )";

        

        shader = new Shader(vertexSrc, fragmentSrc);
        shader->bind();

        cam = new Camera(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0),
                         54.0, 1.77, 0.00001, 100000);


	}
    void Renderer::draw()
    {

        clear();

        glm::mat4 M = glm::mat4(1.0f);        
        glm::mat4 MVP = cam->viewProjection() * M;

        shader->setUniformM4f(MVP,"MVP");
        
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, nullptr);

    }
    void Renderer::clear()
    {
        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
