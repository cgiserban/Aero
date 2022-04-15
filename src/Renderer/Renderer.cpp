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
        txr = new Texture("src/Renderer/Tex/wood_peeling_diff.jpg");
        
        shader->setTexture(0,"texWood",*txr);
        cam = new Camera(glm::vec3(0.0f, 1.5f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
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
        //model = model * translate;
        model = model * glm::rotate(glm::mat4(1.0f), angle , glm::vec3(0.0f, 1.0f, 0.0f));
        

        angle = angle + 0.005;

        glm::mat4 projection = glm::ortho(0, 1, 0, 1);
        glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0,1.0,0.0));

       
        //glm::mat4 MVP = projection * view * model;
        glm::mat4 MVP = cam->viewProjection()* model;

        shader->setUniformM4f(MVP, "MVP");
        obj->draw(shader);

    }

    void Renderer::clear()
    {

        glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    }
}
