#include "DirectionalLight.h"

void DirectionalLight::useDirectionalLight(GLuint colorLocation,
                                           GLuint dirLocation,
                                           GLuint intensityLocation,
                                           GLuint diffuseLocation) {

  useLight(colorLocation, intensityLocation, diffuseLocation);
  glUniform3f(dirLocation, _dir.x, _dir.y, _dir.z);
}
