#include "Light.h"

Light::~Light()
{
}
void Light::useLight(GLuint colorLocation, GLuint posLocation, GLuint intensityLocation, GLuint diffuseLocation) {
	glUniform3f(colorLocation, _col.x, _col.y, _col.z);
	glUniform3f(posLocation, _pos.x, _pos.y, _pos.z);
	glUniform1f(intensityLocation, _intensity);
	glUniform1f(diffuseLocation, _diff_intensity);
	
};