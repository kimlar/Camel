#pragma once

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Include stuff
#include "Math.h"	// PI (with float precision)
#include "Window.h"

const float cameraMinDistance = 0.5f; // Minimum camera distance from colliding objects. Ie. A wall
const float cameraHeight = 1.0f; // Height from floor
const float almostHalfPI = HALF_PI - 0.1f;

class Camera
{
public:
	Camera(Window* window);
	~Camera();

	void Create();
	void Destroy();

	void Update();

	void ResetJumping();
	void CollidedWithCeiling();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	glm::vec3 position;
	float horizontalAngle;
	float verticalAngle;
	float FoV;
	float windowRatio;
	
	float speed;
	float mouseSpeed;
	float jumpSpeed;
	float jumpVelocity;
	bool canJump;
	

	Window* window;
};
