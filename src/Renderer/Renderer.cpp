#include "Renderer.h"
#include "UI/UI.h"
#include "iostream"
namespace Aero 
{
	void Renderer::init()
	{
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        

        std::string vertexSrc = Shader::ParseShader("src/Renderer/Shaders/constant.vert");
        std::string fragmentSrc =Shader::ParseShader("src/Renderer/Shaders/constant.frag");


        shader = new Shader(vertexSrc, fragmentSrc);
        
        
        shader->setTexture(0,"texConcrete","src/Renderer/Tex/wood_peeling_disp.png");
        shader->setTexture(1,"texWood","src/Renderer/Tex/concrete_diff.jpg");
        shader->listTextures();

        cam = new Camera(glm::vec3(1.0f, 1.5f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                         glm::radians(80.0f), 1.77, 0.1f, 100.0f);
        obj = new Object("src/Renderer/Obj/teapot.obj");
	}



    void Renderer::draw()
    {
        clear();
        UI& ui = UI::getInstance();

        cam->setAspect(ui.getWidth() / ui.getHeight());

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate(glm::vec3(0.0f, -1.0f, 0.0f));
        model = model * translate;
        model = model * glm::rotate(glm::mat4(1.0f), angle , glm::vec3(0.0f, 1.0f, 0.0f));
        angle = angle + 0.001;

        glm::mat4 MVP = cam->viewProjection() * model;


        shader->setUniformM4f(MVP, "MVP");




        obj->draw(shader);

    }
    void Renderer::clear()
    {
        //UI& ui = UI::getInstance();

        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glViewport(0, 0, ui.getWidth(), ui.getHeight());
    }
}
