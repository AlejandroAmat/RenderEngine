#define STB_IMAGE_IMPLEMENTATION

#include "cstdio"
#include "Window.h"
#include "Mesh.h"
#include "vector"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Light.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "chrono"

std::vector<Mesh*> objList;
std::vector<Shader> shadersList;
const float toRadians = 3.14159265f / 180.0f;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	//unsigned int indices[] = {
	//	2,3,0,
	//	1,3,2,
	//	0,3,1,
	//	0,1,2
	//};

	GLfloat vertices[] = {
		//	x      y      z			u	  v
			-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,
			0.0f, -1.0f, -1.0f,		0.5f, 0.0f,
			1.0f, -1.0f, 0.0f,		1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f
	};
	
	Mesh* obj1 = new Mesh();
	obj1->createMesh(vertices, indices, 20, 12);
	objList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->createMesh(vertices, indices, 20, 12);
	objList.push_back(obj2);


}



void createShaders() {
	Shader* shader = new Shader();
	shader->createShader("shaders/shader.vert", "shaders/shader.frag");
	shadersList.push_back(*shader);
}
int main() {

	Window mainWindow(800, 600);
	mainWindow.Initialize();
	CreateObjects();
	createShaders();
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformLightPos = 0, unoformLightAmbient = 0, uniformLightColor = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	Texture t1("../Textures/brick.png");
	t1.loadTexture();

	Texture t2("../Textures/dirt.png");
	t2.loadTexture();

	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -180.0f, 0.0f, 5.0f,0.5f);
	std::unique_ptr<Light> lightPtr = std::make_unique<Light>(
		glm::vec3(0.0f, 10.0f, 0.0f),
		glm::vec3(0.7f, 0.5f, 0.8f),
		0.7f
	);
	
	float grad = 0;
	while (!mainWindow.getShouldClose()) {
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;
		printf("FPS: %f\n", 1/deltaTime);
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		glfwSwapInterval(0);
		grad += deltaTime *60;
		shadersList[0].useShader();
		uniformModel = shadersList[0].getModelUniform();
		uniformProjection = shadersList[0].getProjectionUniform();
		uniformView = shadersList[0].getViewUniform();
		uniformLightColor = shadersList[0].getLightColorUniform();
		uniformLightPos = shadersList[0].getLightPosUniform();
		unoformLightAmbient = shadersList[0].getLightAmbientUniform();

		glm::mat4 model = glm::mat4(1.0f); 
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f)); // Optional: Translate if needed
		model = glm::rotate(model, glm::radians(grad), glm::vec3(0.0f, 1.0f, 0.0f)); // Optional: Rotate
		model = glm::scale(model, glm::vec3(1.0f)); // Optional: Scale
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		lightPtr->useLight(uniformLightColor, uniformLightPos, unoformLightAmbient);
		t1.useTexture();
		objList[1]->RenderMesh();

	

		glm::mat4 model_0 = glm::mat4(1.0f);
		model_0 = glm::translate(model_0, glm::vec3(0.0f, 1.0f, -2.4f)); 
		model_0 = glm::rotate(model_0, glm::radians(grad), glm::vec3(0.0f, 1.0f, 0.0f)); // Optional: Rotate
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model_0));
		t2.useTexture();
		objList[0]->RenderMesh();
		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	
}

