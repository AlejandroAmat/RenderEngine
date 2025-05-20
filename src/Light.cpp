#include "Light.h"

Light::~Light() {}
void Light::useLight(GLuint colorLocation, GLuint dirLocation,
                     GLuint intensityLocation, GLuint diffuseLocation) {
  glUniform3f(colorLocation, _col.x, _col.y, _col.z);
  glUniform3f(dirLocation, _dir.x, _dir.y, _dir.z);
  glUniform1f(intensityLocation, _intensity);
  glUniform1f(diffuseLocation, _diff_intensity);
};