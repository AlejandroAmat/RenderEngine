#include "PointLight.h"

void PointLight::usePointLight(GLuint colorLocation, GLuint intensityLocation,
                               GLuint diffuseLocation, GLuint positionLocation,
                               GLuint constantLocation, GLuint linearLocation,
                               GLuint expLocation) {

  useLight(colorLocation, intensityLocation, diffuseLocation);
  glUniform3f(positionLocation, _position.x, _position.y, _position.z);
  glUniform1f(constantLocation, _constant);
  glUniform1f(linearLocation, _linear);
  glUniform1f(expLocation, _exp);
}
