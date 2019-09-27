#pragma once

// Include standard C headers
#include <stdio.h>
#include <stdlib.h>

// Include standard C++ headers
#include <iostream>
#include <string> // FPS

// Include GL3W
#include <GL/gl3w.h>	// TODO: Check if this one is really needed here!

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>


class Window
{
public:
	Window();
	~Window();

	bool Create();
	void Destroy();

	bool Update();
	void RenderBegin();
	void RenderEnd();

	GLFWwindow* glfwWindow;
	int width;
	int height;
	double halfWidth;
	double halfHeight;
	bool quit;

	float deltaTime;
	double previousTime;
	int currentFPS;
	float fpsTime;
	std::string fpsText;

private:
	void SetWindowIcon(std::string filename);

public:
	void ShowMouseCursor();
	void HideMouseCursor();
	bool IsMouseCursorShown();
private:
	bool showMouseCursor;

public:
	//------------------------------- CALLBACKS -------------------------------

	void ConnectCallbacks();

	// Window
	void OnClose(GLFWwindow* window);

	// Keyboard
	bool useChar = false; // false: OnKey, true: OnKeyChar
	void OnKey(GLFWwindow* window, int key, int scancode, int action, int mode);
	bool keys[1024] = { false };
	void OnKeyChar(GLFWwindow* window, unsigned int codepoint, int mods);
	unsigned char keyChar;

	// Mouse
	void OnMouseMove(GLFWwindow* window, double xpos, double ypos);
	double mouseX = 0, mouseY = 0, mouseCameraX = 0, mouseCameraY = 0;
	void OnMouseButton(GLFWwindow* window, int button, int action, int mods);
	bool mouseButtons[8] = { false };
	void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
	double mouseScrollX = 0, mouseScrollY = 0, mouseScrollRelativeX = 0, mouseScrollRelativeY = 0;
};
