#include "Renderer.h"
#include "UI/UI.h"
namespace Aero 
{
	void Renderer::init()
	{

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glfwWindowHint(GLFW_SAMPLES, 4);



        std::string vertexSrc = Shader::ParseShader("src/Renderer/Shaders/constant.vert");
        std::string fragmentSrc =Shader::ParseShader("src/Renderer/Shaders/constant.frag");


        shader = new Shader(vertexSrc, fragmentSrc);
        

        cam = new Camera(glm::vec3(2.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                         glm::radians(80.0f), 1.77f, 0.1f, 100.0f);

        std::string path = "src/Renderer/Obj/monkey.obj";
        obj = new Object(path);        



	}
    void Renderer::draw()
    {
        clear();


        glm::mat4 model = glm::mat4(1.0f);
        model = model * glm::rotate(glm::mat4(1.0f), angle , glm::vec3(1.0f, 0.0f, 0.0f));

        angle += 0.01;

        glm::mat4 MVP = cam->viewProjection() * model;

        shader->setUniformM4f(MVP, "MVP");
        obj->draw(shader);

    }
    void Renderer::clear()
    {
        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
