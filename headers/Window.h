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

		void swapBuffers() { glfwSwapBuffers(m_mainWindow); }

		~Window();
	private:
		GLint m_width;
		GLint m_height;
		GLFWwindow* m_mainWindow;
		GLint m_bufferWidth, m_bufferHeight;
};