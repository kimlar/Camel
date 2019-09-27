#include "CollisionAABB.h"

bool CheckCollisionAABB(glm::vec3 ObjectA, glm::vec3 ObjectB)
{
	const float halfSize = 1.5f; //0.5f;
	if ( (ObjectA.x > (ObjectB.x - halfSize)) && (ObjectA.x < (ObjectB.x + halfSize)))
		if ((ObjectA.y >(ObjectB.y - halfSize)) && (ObjectA.y < (ObjectB.y + halfSize)))
			if ((ObjectA.z >(ObjectB.z - halfSize)) && (ObjectA.z < (ObjectB.z + halfSize)))
				return true;

	return false;
}
