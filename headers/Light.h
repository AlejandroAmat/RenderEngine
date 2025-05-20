#pragma once+
#include "GL/glew.h"
#include <glm.hpp>

class Light
{

public:
	const Light(glm::vec3 pos, glm::vec3 col, GLfloat intensity, GLfloat diffuse_intensity) : _pos(pos), _col(col), _intensity(intensity), _diff_intensity(diffuse_intensity){};
	void useLight(GLuint colorLocation, GLuint posLocation, GLuint intensityLocation, GLuint diffuseLocation);
	~Light();
private:
	const glm::vec3 _pos;
	const glm::vec3 _col;
	const GLfloat _intensity;
	const GLfloat _diff_intensity;
};

