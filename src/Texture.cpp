#include "Texture.h"

Texture::Texture(const char *fileLocation) : m_fileLocation(fileLocation) {}

void Texture::loadTexture() {
  unsigned char *texture =
      stbi_load(m_fileLocation, &m_width, &m_height, &m_bitDepth, 0);
  if (!texture) {
    printf("Failed to find: %s\n", m_fileLocation);
    return;
  }

  glGenTextures(1, &m_textureID);
  glBindTexture(GL_TEXTURE_2D, m_textureID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  GLenum format = (m_bitDepth == 4) ? GL_RGBA : GL_RGB;
  glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format,
               GL_UNSIGNED_BYTE, texture);
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(texture);
}

void Texture::useTexture() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::clearTexture() {

  glDeleteTextures(1, &m_textureID);
  m_textureID = 0;
  m_width = 0;
  m_height = 0;
  m_bitDepth = 0;
  m_fileLocation = "";
}

Texture::~Texture() { clearTexture(); }
