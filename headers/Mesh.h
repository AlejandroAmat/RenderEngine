#pragma once

#include <GL\glew.h>

class Mesh {
public:
  Mesh();
  void createMesh(GLfloat *vertices, unsigned int *indices,
                  unsigned int numOfVertices, unsigned int numOfIndices);
  void RenderMesh();
  void ClearMesh();
  ~Mesh();

private:
  GLuint m_VAO, m_VBO, m_IBO;
  GLsizei m_indexCount;
};