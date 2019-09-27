#pragma once

// Include GL3W
#include <GL/gl3w.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// Include stuff
#include "Shader.h"
#include "Texture.h"
#include "Window.h"



class UIMouseCursor
{
public:
	UIMouseCursor(Window* window);
	~UIMouseCursor(); // Note: should use virtual destructor

	void Create();
	void Destroy();

	void Update();
	void Render();



	Window* window;

	GLFWcursor* cursor;
};
