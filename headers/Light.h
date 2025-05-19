#pragma once+
#include "GL/glew.h"
#include <glm.hpp>

class Light
{

public:
	constexpr Light(glm::vec3 pos, glm::vec3 col, GLfloat intensity) : _pos(pos), _col(col), _intensity(intensity){};
	void useLight(GLuint colorLocation, GLuint posLocation, GLuint intensityLocation);
	~Light();
private:
	const glm::vec3 _pos;
	const glm::vec3 _col;
	const GLfloat _intensity;
};

