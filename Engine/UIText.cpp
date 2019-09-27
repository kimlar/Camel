#include "UIText.h"

UIText::UIText()
{

}

UIText::~UIText()
{

}

void UIText::Create(std::string text, int x, int y, int size)
{
	this->text = text;
	this->x = x;
	this->y = y;
	this->size = size;

	initText2D("Holstein.dds");
}

void UIText::Destroy()
{
	// Delete the text's VBO, the shader and the texture
	cleanupText2D();
}

void UIText::Render()
{
	printText2D(text.c_str(), x, y, size);
}

void UIText::SetText(std::string text)
{
	this->text = text;
}

void UIText::SetPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void UIText::SetSize(int size)
{
	this->size = size;
}
