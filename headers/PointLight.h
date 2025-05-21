#pragma once
#include "Light.h"

class PointLight : public Light {

public:
  const PointLight(const glm::vec3 col, const GLfloat intensity,
                   const GLfloat diffuse_intensity, const glm::vec3 position,
                   GLfloat constant = 1.0f, GLfloat linear = 0.09f,
                   GLfloat exp = 0.032f)
      : Light(col, intensity, diffuse_intensity), _position(position),
        _constant(constant), _linear(linear), _exp(exp){};

  void usePointLight(GLuint colorLocation, GLuint intensityLocation,
                     GLuint diffuseLocation, GLuint positionLocation,
                     GLuint constantLocation, GLuint linearLocation,
                     GLuint expLocation);

private:
  const glm::vec3 _position;
  const GLfloat _constant = 0, _linear = 0, _exp = 0;
};