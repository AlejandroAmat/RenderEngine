#pragma once
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
	const GLuint getViewUniform() const{ return m_uniformView; }
	const GLuint getTextureUniform() const{ return m_uniformTexture; }
	const GLuint getLightColorUniform() const { return m_uniformLightColor; }
	const GLuint getLightPosUniform() const { return m_uniformLightPosition; }
	const GLuint getLightAmbientUniform() const { return m_uniformLightAmbientIntensity; }
	const GLuint getLightDiffuseUniform() const { return m_uniformDiffIntensity; }
	const GLuint getViewPosition() const { return m_uniformCamPosition; }
	~Shader();

private:
	GLuint m_shaderID, m_uniformProjection, m_uniformModel,
		m_uniformView, m_uniformTexture, m_uniformCamPosition,
		m_uniformLightColor, m_uniformLightAmbientIntensity,
		m_uniformLightPosition, m_uniformDiffIntensity;

	void compileShader(const char* vert, const char* frag);
	void addShader(GLuint program, const char* shaderCode, GLenum shaderType);
};