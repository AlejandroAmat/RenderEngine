#include "Light.h"

Light::~Light() {}
void Light::useLight(GLuint colorLocation, GLuint intensityLocation,
                     GLuint diffuseLocation) {
  glUniform3f(colorLocation, _col.x, _col.y, _col.z);
  glUniform1f(intensityLocation, _intensity);
  glUniform1f(diffuseLocation, _diff_intensity);
};