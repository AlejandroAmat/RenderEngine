#include "cstdio"
#include "Window.h"
#include "Mesh.h"
#include "vector"
#include "Shader.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"




std::vector<Mesh*> objList;
std::vector<Shader> shadersList;
const float toRadians = 3.14159265f / 180.0f;

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
			-1.0f, -1.0f, 0.0f,		1.0f, 0.0f,
			0.0f, -1.0f, -1.0f,		0.0f, 1.0f,
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
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	/*glm::mat4 projection = glm::perspective(glm::radians(60.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	projection = glm::mat4(1.0);*/
	glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -1.0f, 1.0f);
	

	float grad = 0;
	while (!mainWindow.getShouldClose()) {
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		grad += 1;
		shadersList[0].useShader();
		uniformModel = shadersList[0].getModelUniform();
		uniformProjection = shadersList[0].getProjectionUniform();
		glm::mat4 model = glm::mat4(1.0f); 
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Optional: Translate if needed
		model = glm::rotate(model, glm::radians(grad), glm::vec3(0.0f, 1.0f, 0.0f)); // Optional: Rotate
		model = glm::scale(model, glm::vec3(1.0f)); // Optional: Scale
	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		objList[1]->RenderMesh();
		glUseProgram(0);
		mainWindow.swapBuffers();
	}

}