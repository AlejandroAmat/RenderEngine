#include "cstdio"
#include "Window.h"

int main() {
	
	Window mainWindow(800, 600);
	mainWindow.Initialize();

	while (!mainWindow.getShouldClose()) {
		glfwPollEvents();
		mainWindow.swapBuffers();
	}

}