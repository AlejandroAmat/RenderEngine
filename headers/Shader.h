#pragma once
#include "stb_image.h"
#include "GL/glew.h"
#include "string"
#include <iostream>
#include <fstream>

class Shader {
public:
	Shader();
	void createShader(const char* vert, const char* frag);
	std::string ReadFile(const char* fileLocation);
	void useShader();
	void clearShader();

	const GLuint getProjectionUniform() const{ return m_uniformProjection; }
	const GLuint getModelUniform() const{ return m_uniformModel; }
	~Shader();

private:
	GLuint m_shaderID, m_uniformProjection, m_uniformModel, m_uniformView;
	void compileShader(const char* vert, const char* frag);
	void addShader(GLuint program, const char* shaderCode, GLenum shaderType);
};