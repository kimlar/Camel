#pragma once

#include <string>

class ImagePng
{
public:
	ImagePng(std::string filename, bool alpha = true);
	~ImagePng();

	unsigned char* GetImage();
	int GetWidth();
	int GetHeight();
	bool IsAlpha();

private:
	unsigned char* image;
	int w;
	int h;
	bool isAlpha;
};


//
// How to load it as an OpenGL texture
//

/*
GLuint m_texture;

std::string filename = "myfile.png";
int w;
int h;
int comp;
unsigned char* image = stbi_load(filename.c_str(), &w, &h, &comp, STBI_rgb_alpha); // STBI_rgb

if (image == nullptr)
throw(std::string("Failed to load texture"));

glGenTextures(1, &m_texture);

glBindTexture(GL_TEXTURE_2D, m_texture);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

if (comp == 3)
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
else if (comp == 4)
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

glBindTexture(GL_TEXTURE_2D, 0);

stbi_image_free(image);
*/
