#include "PointLight.h"

void PointLight::useLight(GLuint colorLocation, GLuint dirLocation,
                          GLuint intensityLocation, GLuint diffuseLocation,
                          GLuint positionLocation) {
  glUniform3f(colorLocation, _col.x, _col.y, _col.z);
  glUniform3f(dirLocation, _dir.x, _dir.y, _dir.z);
  glUniform1f(intensityLocation, _intensity);
  glUniform1f(diffuseLocation, _diff_intensity);
  glUniform3f(positionLocation, _position.x, _position.y, _position.z);
}
