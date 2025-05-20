#pragma once +
#include "GL/glew.h"
#include <glm.hpp>

class Light {

public:
  const Light(glm::vec3 dir, glm::vec3 col, GLfloat intensity,
              GLfloat diffuse_intensity)
      : _dir(dir), _col(col), _intensity(intensity),
        _diff_intensity(diffuse_intensity){};
  void useLight(GLuint colorLocation, GLuint dirLocation,
                GLuint intensityLocation, GLuint diffuseLocation);
  ~Light();

protected:
  const glm::vec3 _dir;
  const glm::vec3 _col;
  const GLfloat _intensity;
  const GLfloat _diff_intensity;
};
