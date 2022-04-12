#include "Renderer.h"
#include "UI/UI.h"
namespace Aero 
{
	void Renderer::init()
	{
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);

        std::string vertexSrc = Shader::ParseShader("src/Renderer/Shaders/constant.vert");
        std::string fragmentSrc =Shader::ParseShader("src/Renderer/Shaders/constant.frag");


        shader = new Shader(vertexSrc, fragmentSrc);
        shader2 = new Shader(vertexSrc, fragmentSrc);

        cam = new Camera(glm::vec3(1.0f, 1.5f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                         glm::radians(80.0f), 1.77f, 0.1f, 100.0f);


        obj = new Object("src/Renderer/Obj/gadet.obj");
        obj2 = new Object("src/Renderer/Obj/monkey.fbx");

        

	}
    void Renderer::draw()
    {
        clear();


        glm::mat4 M = glm::mat4(1.0f);

        glm::mat4 model = glm::mat4(1.0f);
        model = model * glm::rotate(glm::mat4(1.0f), angle , glm::vec3(0.0f, 1.0f, 0.0f));
        angle = angle + 0.001;

        glm::mat4 MVP = cam->viewProjection() * model;
        glm::mat4 MVP2 = cam->viewProjection() * M;

        shader->setUniformM4f(MVP, "MVP");
        shader2->setUniformM4f(MVP2, "MVP");

        
        obj->draw(shader);
        obj2->draw(shader2);




    }
    void Renderer::clear()
    {
        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
