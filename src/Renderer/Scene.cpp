#include "Scene.h"
#include "UI/UI.h"

namespace Aero
{

	void Scene::createScene()
	{
		
		std::string vertexSrc = Shader::ParseShader("src/Renderer/Shaders/diffuse.vert");
		std::string fragmentSrc = Shader::ParseShader("src/Renderer/Shaders/diffuse.frag");

		std::string vertexSrc2 = Shader::ParseShader("src/Renderer/Shaders/constant.vert");
		std::string fragmentSrc2 = Shader::ParseShader("src/Renderer/Shaders/constant.frag");

		mainShader = new Shader(vertexSrc, fragmentSrc);
		constantShader = new Shader(vertexSrc2, fragmentSrc2);


		diffColor = new Texture("src/Renderer/Tex/wood_peeling_diff.jpg");
		
		mainShader->setTexture(0, "texWood", *diffColor);
		constantShader->setTexture(0, "texWood", *diffColor);


		teapot = new Object("src/Renderer/Obj/teapot.obj");
		teapot->addShader(mainShader);

		pointLight = new Light(glm::vec3(0.0, 3.5, 0.5), glm::vec4(1.0, 0.5, 0.5, 1.0), 0.5);
		defaultCam = new Camera(glm::vec3(0.0f, 1.5f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
							 glm::radians(80.0f), 1.77, 0.1f, 100.0f);

	}

	void Scene::render()
	{

		UI& ui = UI::getInstance();

		defaultCam->setAspect(ui.getWidth() / ui.getHeight());


		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 translate = glm::translate(glm::vec3(0.0f, -1.0f, 0.0f));
		model = model * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));


		angle = angle + 0.005;

		//glm::mat4 MVP = projection * view * model;
		glm::mat4 MVP = defaultCam->viewProjection() * model;

		mainShader->setUniformM4f(MVP, "MVP");
		constantShader->setUniformM4f(MVP, "MVP");

		mainShader->setUniform3f(pointLight->getPos(), "lightPos");
		mainShader->setUniform4f(pointLight->getColor(), "lightColor");
		mainShader->setUniformf(pointLight->getIntensity(), "lightIntensity");

		teapot->draw();
		if (angle > 5.0) teapot->addShader(constantShader);

	}

}