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
	createCallbacks();
	//glfwSetInputMode(m_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(m_mainWindow, GLFW_STICKY_KEYS, GLFW_FALSE);

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
	glfwSetWindowUserPointer(m_mainWindow, this);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}
void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;

			printf("true");
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			printf("false");
		}
	}
}
void Window::createCallbacks()
{
	glfwSetKeyCallback(m_mainWindow, handleKeys);
	glfwSetCursorPosCallback(m_mainWindow, handleMouse);
}
void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}
Window::~Window()
{
	glfwDestroyWindow(m_mainWindow);
	glfwTerminate();
}
