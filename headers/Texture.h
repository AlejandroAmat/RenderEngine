#pragma once
#include "stb_image.h"

#include "GL/glew.h"


class Texture {
	public:
		Texture(const char* fileLocation);

		void loadTexture();
		void useTexture();
		void clearTexture();
		~Texture();
	private:
		const char* m_fileLocation;
		GLuint m_textureID = 0;
		int m_width=0, m_height=0, m_bitDepth = 0;
};