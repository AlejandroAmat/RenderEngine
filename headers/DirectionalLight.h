#pragma once
#include "Light.h"

class DirectionalLight : public Light {

public:
  const DirectionalLight(const glm::vec3 col, const GLfloat intensity,
                         const GLfloat diffuse_intensity, const glm::vec3 dir)
      : Light(col, intensity, diffuse_intensity), _dir(dir){};

  void useDirectionalLight(GLuint colorLocation, GLuint dirLocation,
                           GLuint intensityLocation, GLuint diffuseLocation);

private:
  glm::vec3 _dir;
};