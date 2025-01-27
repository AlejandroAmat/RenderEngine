#include "Window.h"

Window::Window()
{
	m_width = 800;
	m_height = 600;
	//keys and mouse logic
}

Window::Window(GLint width, GLint height) : m_height(height), m_width(width)
{

}

int Window::Initialize()
{	
	if (!glfwInit())
	{
		printf("Error using glfw");
		glfwTerminate();
		return -1;
	}
	//GLFW properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatiblity
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//create window
	m_mainWindow = glfwCreateWindow(m_width, m_height, "Render Engine", NULL, NULL);
	if (!m_mainWindow)
	{
		printf("Error creating GLFW window!");
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(m_mainWindow, &m_bufferWidth, &m_bufferHeight);
	glfwMakeContextCurrent(m_mainWindow);

	//mouse + key

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("Error: %s", glewGetErrorString(error));
		glfwDestroyWindow(m_mainWindow);
		glfwTerminate();
		return 1;
	}
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, m_bufferWidth, m_bufferHeight);

	//mouse and key pointer
}


Window::~Window()
{
	glfwDestroyWindow(m_mainWindow);
	glfwTerminate();
}
