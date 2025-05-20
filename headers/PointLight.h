#pragma once
#include "Light.h"

class PointLight : public Light {

public:
  const PointLight(const glm::vec3 dir, const glm::vec3 col,
                   const GLfloat intensity, const GLfloat diffuse_intensity,
                   const glm::vec3 position)
      : Light(dir, col, intensity, diffuse_intensity), _position(position){};

  void useLight(GLuint colorLocation, GLuint dirLocation,
                GLuint intensityLocation, GLuint diffuseLocation,
                GLuint positionLocation);

private:
  glm::vec3 _position;
  GLfloat _constant = 0, _linear = 0, _exp = 0;
};