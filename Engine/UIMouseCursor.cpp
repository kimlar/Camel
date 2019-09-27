#include "UIMouseCursor.h"

#include "ImagePng.h"

UIMouseCursor::UIMouseCursor(Window* window)
{
	this->window = window;
}

UIMouseCursor::~UIMouseCursor()
{
	this->window = nullptr;
}

void UIMouseCursor::Create()
{




	ImagePng* image = new ImagePng("mouse-cursor-001.png");

	GLFWimage* glfwImage = new GLFWimage();
	glfwImage->width = image->GetWidth();
	glfwImage->height = image->GetHeight();
	glfwImage->pixels = image->GetImage();
	int hotx = 1;
	int hoty = 1;
	cursor = glfwCreateCursor(glfwImage, hotx, hoty);
	glfwSetCursor(this->window->glfwWindow, cursor);

	delete image;
	delete glfwImage;
}

void UIMouseCursor::Destroy()
{
	glfwDestroyCursor(cursor);
}

void UIMouseCursor::Update()
{
}

void UIMouseCursor::Render()
{

}
