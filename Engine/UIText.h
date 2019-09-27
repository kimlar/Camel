#pragma once

// Include C++ standard headers
#include <string>

// Include engine stuff
#include "text2D.h"

class UIText
{
public:
	UIText();
	~UIText();

	void Create(std::string text, int x, int y, int size);
	void Destroy();

	void Render();

	void SetText(std::string text);
	void SetPosition(int x, int y);
	void SetSize(int size);

private:
	std::string text;
	int x;
	int y;
	int size;
};
