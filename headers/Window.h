#pragma once
#include "GL/glew.h"
#include "glfw3.h"
#include "cstdio"
#include <memory>
#include <iostream>

class Window {
	public:
		Window();
		Window(GLint width, GLint height);

		int Initialize();
		bool getShouldClose() { return glfwWindowShouldClose(m_mainWindow); }
		GLint getBufferWidth() { return m_bufferWidth; }
		GLint getBufferHeight() { return m_bufferHeight; }

		bool* getsKeys() { return keys; }
		GLfloat getXChange();
		GLfloat getYChange();
		void swapBuffers() { glfwSwapBuffers(m_mainWindow); }

		~Window();
	private:
		GLint m_width;
		GLint m_height;
		GLFWwindow* m_mainWindow;
		GLint m_bufferWidth, m_bufferHeight;

		bool keys[1024];

		GLfloat lastX;
		GLfloat lastY;
		GLfloat xChange;
		GLfloat yChange;
		bool mouseFirstMoved;

		void createCallbacks();
		static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
		static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};