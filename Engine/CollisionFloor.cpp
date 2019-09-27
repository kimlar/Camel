#include "CollisionFloor.h"

bool CheckCollisionFloor(glm::vec3 ObjectA, glm::vec3 ObjectB)
{
	const float halfSize = 1.0f + 0.5f;
	//const float collisionDepth = 1.0f;
	if ((ObjectA.x > (ObjectB.x - halfSize)) && (ObjectA.x < (ObjectB.x + halfSize)))
		if ((ObjectA.y > (ObjectB.y - halfSize)) && (ObjectA.y < ObjectB.y))
			if ((ObjectA.z > (ObjectB.z - halfSize)) && (ObjectA.z < (ObjectB.z + halfSize)))
					return true;

	return false;
}
