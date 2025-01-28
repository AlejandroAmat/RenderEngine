#include "Shader.h"

Shader::Shader()
{
	m_shaderID = 0;
	m_uniformModel = 0;
	m_uniformProjection = 0;
	m_uniformView = 0;
	m_uniformTexture = 0;
}

void Shader::createShader(const char* vert, const char* frag)
{
	std::string vertexCode = ReadFile(vert);
	std::string fragmentCode = ReadFile(frag);
	const char* vertCode = vertexCode.c_str();
	const char* fragCode = fragmentCode.c_str();
	compileShader(vertCode, fragCode);
}

std::string Shader::ReadFile(const char* fileLocation)
{	
	std::string shaderCode;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Error loading Shaders");
		return "";
	}
	std::string line;
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		shaderCode.append(line + "\n");
	}
	fileStream.close();
	return shaderCode;
}

void Shader::useShader()
{
	glUseProgram(m_shaderID);
}

void Shader::clearShader()
{
	if (m_shaderID != 0) {
		glDeleteProgram(m_shaderID);
		m_shaderID = 0;
	}
	m_uniformModel = 0;
	m_uniformProjection = 0;
	m_uniformView = 0;
	m_uniformTexture = 0;
}

Shader::~Shader()
{
	clearShader();
}

void Shader::compileShader(const char* vert, const char* frag)
{
	m_shaderID = glCreateProgram();
	if (!m_shaderID) {
		printf("error creating shader program");
		return;
	}

	addShader(m_shaderID, vert, GL_VERTEX_SHADER);
	addShader(m_shaderID, frag, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}
	glValidateProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	m_uniformProjection = glGetUniformLocation(m_shaderID, "projection");
	m_uniformModel = glGetUniformLocation(m_shaderID, "model");
	m_uniformView = glGetUniformLocation(m_shaderID, "view");
	m_uniformTexture = glGetUniformLocation(m_shaderID, "theTexture");

	
}

void Shader::addShader(GLuint program, const char* shaderCode, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	GLint shaderLength = strlen(shaderCode);

	glShaderSource(shader, 1, &shaderCode, &shaderLength);
	glCompileShader(shader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(m_shaderID, shader);
}

