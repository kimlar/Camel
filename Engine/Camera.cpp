#include "Camera.h"

Camera::Camera(Window* window)
{
	this->window = window;
}

Camera::~Camera()
{
	this->window = nullptr;
}

void Camera::Create()
{
	// Initial position : on +Z
	position = glm::vec3(-2, cameraHeight, 4);
	// Initial horizontal angle : toward -Z
	horizontalAngle = PI;
	// Initial vertical angle : none
	verticalAngle = 0.0f;
	// Initial Field of View
	FoV = 45.0f;
	// Initial window width/height ratio
	windowRatio = float(window->width) / float(window->height);
	
	
	speed = 10.0f; //3.0f; // 3 units / second
	mouseSpeed = 0.005f; //0.005f
	jumpSpeed = 5.0f;
}

void Camera::Destroy()
{

}

void Camera::Update()
{
	// Gravity on player
	position.y += jumpVelocity * window->deltaTime;
	if (position.y < 0)
	{
		position.y = 0.0f;
		ResetJumping(); // floor height
	}
	else
	{
		jumpVelocity -= 9.81f * window->deltaTime;
	}


	if (!window->IsMouseCursorShown())
	{
		// Compute new orientation
		horizontalAngle += mouseSpeed * float(window->halfWidth - window->mouseCameraX);
		verticalAngle += mouseSpeed * float(window->halfHeight - window->mouseCameraY);
		if (verticalAngle > (almostHalfPI))
			verticalAngle = almostHalfPI;
		if (verticalAngle < -almostHalfPI)
			verticalAngle = -almostHalfPI;
		window->mouseCameraX = window->halfWidth;
		window->mouseCameraY = window->halfHeight;
	}

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - HALF_PI),
		0,
		cos(horizontalAngle - HALF_PI)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (window->keys[GLFW_KEY_W] == GLFW_PRESS)
	{
		position.x += direction.x * window->deltaTime * speed;
		position.z += direction.z * window->deltaTime * speed;
	}
	// Move backward
	if (window->keys[GLFW_KEY_S] == GLFW_PRESS)
	{
		position.x -= direction.x * window->deltaTime * speed;
		position.z -= direction.z * window->deltaTime * speed;
	}
	// Strafe right
	if (window->keys[GLFW_KEY_D] == GLFW_PRESS)
	{
		position += right * window->deltaTime * speed;
	}
	// Strafe left
	if (window->keys[GLFW_KEY_A] == GLFW_PRESS)
	{
		position -= right * window->deltaTime * speed;
	}
	// Jump
	if (window->keys[GLFW_KEY_SPACE] == GLFW_PRESS)
	{
		if (canJump)
		{
			canJump = false;
			jumpVelocity = jumpSpeed;
			//position += up * window->deltaTime * jumpVelocity;
		}
	}
	
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), windowRatio, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);
}

void Camera::ResetJumping()
{
	canJump = true;
	jumpVelocity = 0.0f;
}

void Camera::CollidedWithCeiling()
{
	jumpVelocity = 0.0f;
}

glm::mat4 Camera::getViewMatrix()
{
	return ViewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return ProjectionMatrix;
}
