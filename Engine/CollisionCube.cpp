#include "CollisionCube.h"

#include "Camera.h"

bool CheckCollisionCubeXP(glm::vec3 ObjectA, glm::vec3 ObjectB)
{
	const float halfSize = 1.0f;
	if ((ObjectA.x > (ObjectB.x - halfSize - cameraMinDistance)) && (ObjectA.x < (ObjectB.x)))
		if ((ObjectA.y > (ObjectB.y - halfSize)) && (ObjectA.y < (ObjectB.y + halfSize)))
			if ((ObjectA.z > (ObjectB.z - halfSize)) && (ObjectA.z < (ObjectB.z + halfSize)))
				return true;

	return false;
}

bool CheckCollisionCubeXN(glm::vec3 ObjectA, glm::vec3 ObjectB)
{
	const float halfSize = 1.0f;
	if ((ObjectA.x > (ObjectB.x)) && (ObjectA.x < (ObjectB.x + halfSize + cameraMinDistance)))
		if ((ObjectA.y > (ObjectB.y - halfSize)) && (ObjectA.y < (ObjectB.y + halfSize)))
			if ((ObjectA.z > (ObjectB.z - halfSize)) && (ObjectA.z < (ObjectB.z + halfSize)))
				return true;

	return false;
}

bool CheckCollisionCubeYP(glm::vec3 ObjectA, glm::vec3 ObjectB)
{
	const float halfSize = 1.0f;
	if ((ObjectA.x > (ObjectB.x - halfSize)) && (ObjectA.x < (ObjectB.x + halfSize)))
		if ((ObjectA.y > (ObjectB.y - halfSize - cameraMinDistance)) && (ObjectA.y < (ObjectB.y)))
			if ((ObjectA.z > (ObjectB.z - halfSize)) && (ObjectA.z < (ObjectB.z + halfSize)))
				return true;

	return false;
}

bool CheckCollisionCubeYN(glm::vec3 ObjectA, glm::vec3 ObjectB)
{
	const float halfSize = 1.0f;
	if ((ObjectA.x > (ObjectB.x - halfSize)) && (ObjectA.x < (ObjectB.x + halfSize )))
		if ((ObjectA.y > (ObjectB.y)) && (ObjectA.y < (ObjectB.y + halfSize + cameraMinDistance + cameraHeight)))
			if ((ObjectA.z > (ObjectB.z - halfSize)) && (ObjectA.z < (ObjectB.z + halfSize)))
				return true;

	return false;
}

bool CheckCollisionCubeZP(glm::vec3 ObjectA, glm::vec3 ObjectB)
{
	const float halfSize = 1.0f;
	if ((ObjectA.x > (ObjectB.x - halfSize)) && (ObjectA.x < (ObjectB.x + halfSize)))
		if ((ObjectA.y > (ObjectB.y - halfSize)) && (ObjectA.y < (ObjectB.y + halfSize)))
			if ((ObjectA.z > (ObjectB.z - halfSize - cameraMinDistance)) && (ObjectA.z < (ObjectB.z)))
				return true;

	return false;
}

bool CheckCollisionCubeZN(glm::vec3 ObjectA, glm::vec3 ObjectB)
{
	const float halfSize = 1.0f;
	if ((ObjectA.x > (ObjectB.x - halfSize)) && (ObjectA.x < (ObjectB.x + halfSize)))
		if ((ObjectA.y > (ObjectB.y - halfSize)) && (ObjectA.y < (ObjectB.y + halfSize)))
			if ((ObjectA.z > (ObjectB.z)) && (ObjectA.z < (ObjectB.z + halfSize + cameraMinDistance)))
				return true;

	return false;
}
