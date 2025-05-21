#pragma once
#include "DirectionalLight.h"
#include "GL/glew.h"
#include "PointLight.h"
#include "string"
#include <fstream>
#include <iostream>
struct Directional {

  GLuint uniformColor;
  GLuint uniformAmbient;
  GLuint uniformDiffuse;
  GLuint uniformDir;

  Directional()
      : uniformAmbient(0), uniformColor(0), uniformDiffuse(0), uniformDir(0){};
};

struct Point {

  GLuint uniformColor;
  GLuint uniformAmbient;
  GLuint uniformDiffuse;

  GLuint uniformPosition;
  GLuint uniformConstant;
  GLuint uniformLinear;
  GLuint uniformExp;

  Point()
      : uniformAmbient(0), uniformColor(0), uniformDiffuse(0),
        uniformPosition(0), uniformConstant(0), uniformLinear(0),
        uniformExp(0){};
};

class Shader {
public:
  Shader();
  void createShader(const char *vert, const char *frag);
  std::string ReadFile(const char *fileLocation);
  void useShader();
  void clearShader();

  const void useDirectionalLight(std::unique_ptr<DirectionalLight> &light) {
    light->useDirectionalLight(
        _directional.uniformColor, _directional.uniformDir,
        _directional.uniformAmbient, _directional.uniformDiffuse);
  }

  const void usePointLight(std::unique_ptr<PointLight> &light) {
    light->usePointLight(_point.uniformColor, _point.uniformAmbient,
                         _point.uniformDiffuse, _point.uniformPosition,
                         _point.uniformConstant, _point.uniformLinear,
                         _point.uniformExp);
  }

  const GLuint getProjectionUniform() const { return m_uniformProjection; }
  const GLuint getModelUniform() const { return m_uniformModel; }
  const GLuint getViewUniform() const { return m_uniformView; }
  const GLuint getTextureUniform() const { return m_uniformTexture; }

  ~Shader();

private:
  GLuint m_shaderID, m_uniformProjection, m_uniformModel, m_uniformView,
      m_uniformTexture, m_uniformCamPosition;
  Directional _directional;
  Point _point;
  void compileShader(const char *vert, const char *frag);
  void addShader(GLuint program, const char *shaderCode, GLenum shaderType);
};