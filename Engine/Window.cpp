#include "Window.h"

#include "ImagePng.h"

Window::Window()
{

}

Window::~Window()
{

}

bool Window::Create()
{
	
	// Requested OpenGL version
	const int ContextVersionMajor = 4;
	const int ContextVersionMinor = 3;

	// Initial window width, height
	width = 1024;
	height = 768;
	halfWidth = width / 2;
	halfHeight = height / 2;
	
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false; // Failed
	}

	// Configure the window and the context
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ContextVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ContextVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a window and OpenGL context
	glfwWindow = glfwCreateWindow(width, height, "Camel Engine", NULL, NULL);
	if (glfwWindow == NULL) {
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		return false; // Failed
	}
	glfwMakeContextCurrent(glfwWindow);


	// Initialize GL3W
	if (gl3wInit()) {
		fprintf(stderr, "Failed to initialize OpenGL\n");
		glfwTerminate();
		return false; // Failed
	}
	// Is the requested OpenGL supported?
	if (!gl3wIsSupported(ContextVersionMajor, ContextVersionMinor)) {
		fprintf(stderr, "OpenGL %i.%i not supported", ContextVersionMajor, ContextVersionMinor);
		glfwTerminate();
		return false; // Failed
	}

	// VSync ?
	bool vSync = false;
	if(vSync)
		glfwSwapInterval(1);


	// Window icon
	SetWindowIcon("Camel.png");
	
	// Configure inputs
	glfwSetInputMode(glfwWindow, GLFW_STICKY_KEYS, GL_TRUE); // Make the pressed keys to be registered as pressed until we check it with glfwGetKey
	glfwSetInputMode(glfwWindow, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE); // Make the pressed mouse button to be registered as pressed until we check it with glfwGetMouseButton
	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hide the mouse cursor and grabs the cursor
	

	// A little callback hack
	ConnectCallbacks();

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(glfwWindow, halfWidth, halfHeight);
	mouseX = halfWidth;
	mouseY = halfHeight;
	mouseCameraX = halfWidth;
	mouseCameraY = halfHeight;

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Set the clear color to dark blue background		

	// Initialize game timer and FPS
	previousTime = glfwGetTime();
	currentFPS = 0;
	fpsTime = 0.0f;

	return true; // Success!
}

void Window::Destroy()
{
	// Show the mouse cursor and release the cursor
	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

bool Window::Update()
{
	// Get delta time
	double currentTime = glfwGetTime();
	deltaTime = float(currentTime - previousTime);
	previousTime = currentTime;

	// Get frame per second (FPS)
	currentFPS++;
	fpsTime += deltaTime;
	if (fpsTime >= 1.0f)
	{
		// Update FPS
		fpsText = "FPS: " + std::to_string(currentFPS);
		//fpsText += ", Mouse: " + std::to_string(mouseX) + "," + std::to_string(mouseY); // TODO: Remove this debug line!
		//glfwSetWindowTitle(glfwWindow, fpsText.c_str());

		// Reset it
		currentFPS = 0;
		fpsTime -= 1.0f;
	}
	
	// Get events
	glfwPollEvents();

	// Check window
	if (glfwWindowShouldClose(glfwWindow))
		return false; // Quit the game

	// Check input
	//if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	return false; // Quit the game

	// Outside wanting to quit
	if(this->quit)
		return false; // Quit the game

	// Reset mouse position for next frame
	if (!IsMouseCursorShown())
		glfwSetCursorPos(glfwWindow, halfWidth, halfHeight);

	return true; // Continue running the game
}

void Window::RenderBegin()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
}

void Window::RenderEnd()
{
	// Swap buffers
	glfwSwapBuffers(glfwWindow);
}

void Window::SetWindowIcon(std::string filename)
{
	/*
	int w;
	int h;
	int comp;
	unsigned char* image = stbi_load(filename.c_str(), &w, &h, &comp, STBI_rgb_alpha); // STBI_rgb

	if (image == nullptr)
		throw(std::string("Failed to load texture"));

	GLFWimage* glfwImage = new GLFWimage();
	glfwImage->width = w;
	glfwImage->height = h;
	glfwImage->pixels = image;


	// Window icon
	glfwSetWindowIcon(glfwWindow, 1, glfwImage);
	
	// Free it
	stbi_image_free(image);

	// Delete glfwImage?
	*/

	ImagePng* image = new ImagePng(filename);
	
	GLFWimage* glfwImage = new GLFWimage();
	glfwImage->width = image->GetWidth();
	glfwImage->height = image->GetHeight();
	glfwImage->pixels = image->GetImage();
	
	// Window icon
	glfwSetWindowIcon(glfwWindow, 1, glfwImage);

	delete image;
	delete glfwImage;
}

void Window::ShowMouseCursor()
{
	showMouseCursor = true;
	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Hide the mouse cursor and grabs the cursor
}

void Window::HideMouseCursor()
{
	showMouseCursor = false;
	glfwSetCursorPos(glfwWindow, halfWidth, halfHeight);
	mouseCameraX = halfWidth;
	mouseCameraY = halfHeight;
	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hide the mouse cursor and grabs the cursor
}

bool Window::IsMouseCursorShown()
{
	return showMouseCursor;
}

void Window::ConnectCallbacks()
{
	//
	// This is a hack to from "C callback" to "C++ class method".
	//

	glfwSetWindowUserPointer(this->glfwWindow, this);

	// OnClose
	auto funcOnClose = [](GLFWwindow* window)
	{
		static_cast<Window*>(glfwGetWindowUserPointer(window))->OnClose(window);
	};
	glfwSetWindowCloseCallback(this->glfwWindow, funcOnClose);

	// OnKey
	auto funcOnKey = [](GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		static_cast<Window*>(glfwGetWindowUserPointer(window))->OnKey(window, key, scancode, action, mode);
	};
	glfwSetKeyCallback(this->glfwWindow, funcOnKey);

	//OnKeyChar
	auto funcOnKeyChar = [](GLFWwindow* window, unsigned int codepoint, int mods)
	{
		static_cast<Window*>(glfwGetWindowUserPointer(window))->OnKeyChar(window, codepoint, mods);
	};
	glfwSetCharModsCallback(this->glfwWindow, funcOnKeyChar);

	// OnMouseMove
	auto funcOnMouseMove = [](GLFWwindow* window, double xpos, double ypos)
	{
		static_cast<Window*>(glfwGetWindowUserPointer(window))->OnMouseMove(window, xpos, ypos);
	};
	glfwSetCursorPosCallback(this->glfwWindow, funcOnMouseMove);
		
	// OnMouseButton
	auto funcOnMouseButton = [](GLFWwindow* window, int button, int action, int mods)
	{
		static_cast<Window*>(glfwGetWindowUserPointer(window))->OnMouseButton(window, button, action, mods);
	};
	glfwSetMouseButtonCallback(this->glfwWindow, funcOnMouseButton);

	// OnMouseScroll
	auto funcOnMouseScroll = [](GLFWwindow* window, double xoffset, double yoffset)
	{
		static_cast<Window*>(glfwGetWindowUserPointer(window))->OnMouseScroll(window, xoffset, yoffset);
	};
	glfwSetScrollCallback(this->glfwWindow, funcOnMouseScroll);
}

void Window::OnClose(GLFWwindow* window)
{
	//glfwSetWindowShouldClose(window, GLFW_FALSE); // To cancel the window close signal
	//	
	//printf("OnClose:\n");
}

void Window::OnKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Update 
	if (!useChar)
	{
		if (key >= 0 && key < 1024)
		{
			if (action == GLFW_PRESS)
				keys[key] = true;
			else if (action == GLFW_RELEASE)
				keys[key] = false;
		}

		//printf("OnKey: %i Pressed/Released\n", key);
	}
}

void Window::OnKeyChar(GLFWwindow* window, unsigned int codepoint, int mods)
{
	// NOTE #1: There is two modes for receiving Unicode text: glfwSetCharCallback and glfwSetCharModsCallback
	// NOTE #2: This is not working as intended. A workaround hack is to cap the character to 128.

	// Update
	if (useChar)
	{
		// Ugly hack!
		if (codepoint < 128) // At least give us ASCII
			keyChar = codepoint;

		//printf("%c", keyChar);
	}
}

void Window::OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
	// Update
	//mouseRelativeX = xpos - mouseX;
	//mouseRelativeY = mouseY - ypos; // Reversed since y-coordinates go from bottom to left
	mouseX = xpos;
	mouseY = ypos;
	mouseCameraX = xpos;
	mouseCameraY = ypos;

	//printf("OnMouseMove: Absolute: %f,%f. Relative: %f,%f\n", mouseX, mouseY, mouseRelativeX, mouseRelativeY);
}

void Window::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	// Update
	if (button >= 0 && button < 8)
	{
		if (action == GLFW_PRESS)
			mouseButtons[button] = true;
		else if (action == GLFW_RELEASE)
			mouseButtons[button] = false;
	}

	//printf("OnMouseButton: %i Pressed/Released\n", button);
}

void Window::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	// Update
	mouseScrollX += xoffset;
	mouseScrollY += yoffset;
	mouseScrollRelativeX = xoffset;
	mouseScrollRelativeY = yoffset;

	//printf("OnMouseScroll: Absolute: %f,%f. Relative: %f,%f\n", mouseScrollX, mouseScrollY, mouseScrollRelativeX, mouseScrollRelativeY);
}
