#include "ImagePng.h"

#ifndef STBI_ONLY_PNG
#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif // !STBI_ONLY_PNG

ImagePng::ImagePng(std::string filename, bool alpha)
{
	this->isAlpha = alpha;
	
	// Load image
	int comp;
	if(alpha)
		image = stbi_load(filename.c_str(), &w, &h, &comp, STBI_rgb_alpha); // STBI_rgb
	else
		image = stbi_load(filename.c_str(), &w, &h, &comp, STBI_rgb);

	if (image == nullptr)
		throw(std::string("Failed to load texture"));
}

ImagePng::~ImagePng()
{
	stbi_image_free(image);
}

unsigned char* ImagePng::GetImage()
{
	return image;
}

int ImagePng::GetWidth()
{
	return w;
}

int ImagePng::GetHeight()
{
	return h;
}

bool ImagePng::IsAlpha()
{
	return isAlpha;
}
