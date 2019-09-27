#include "TriggerLocation.h"

TriggerLocation::TriggerLocation(glm::vec3 location)
{
	this->location = location;
}

TriggerLocation::~TriggerLocation()
{

}

bool TriggerLocation::CheckTrigger(glm::vec3 Object)
{
	if (CheckCollisionCubeXP(Object))
		return true;
	if (CheckCollisionCubeXN(Object))
		return true;
	if (CheckCollisionCubeYP(Object))
		return true;
	if (CheckCollisionCubeYN(Object))
		return true;
	if (CheckCollisionCubeZP(Object))
		return true;
	if (CheckCollisionCubeZN(Object))
		return true;

	return false;
}


bool TriggerLocation::CheckCollisionCubeXP(glm::vec3 Object)
{
	const float halfSize = 1.0f;
	if ((Object.x > (this->location.x - halfSize)) && (Object.x < (this->location.x)))
		if ((Object.y > (this->location.y - halfSize)) && (Object.y < (this->location.y + halfSize)))
			if ((Object.z > (this->location.z - halfSize)) && (Object.z < (this->location.z + halfSize)))
				return true;

	return false;
}

bool TriggerLocation::CheckCollisionCubeXN(glm::vec3 Object)
{
	const float halfSize = 1.0f;
	if ((Object.x > (this->location.x)) && (Object.x < (this->location.x + halfSize)))
		if ((Object.y > (this->location.y - halfSize)) && (Object.y < (this->location.y + halfSize)))
			if ((Object.z > (this->location.z - halfSize)) && (Object.z < (this->location.z + halfSize)))
				return true;

	return false;
}

bool TriggerLocation::CheckCollisionCubeYP(glm::vec3 Object)
{
	const float halfSize = 1.0f;
	if ((Object.x > (this->location.x - halfSize)) && (Object.x < (this->location.x + halfSize)))
		if ((Object.y > (this->location.y - halfSize)) && (Object.y < (this->location.y)))
			if ((Object.z > (this->location.z - halfSize)) && (Object.z < (this->location.z + halfSize)))
				return true;

	return false;
}

bool TriggerLocation::CheckCollisionCubeYN(glm::vec3 Object)
{
	const float halfSize = 1.0f;
	if ((Object.x > (this->location.x - halfSize)) && (Object.x < (this->location.x + halfSize)))
		if ((Object.y > (this->location.y)) && (Object.y < (this->location.y + halfSize)))
			if ((Object.z > (this->location.z - halfSize)) && (Object.z < (this->location.z + halfSize)))
				return true;

	return false;
}

bool TriggerLocation::CheckCollisionCubeZP(glm::vec3 Object)
{
	const float halfSize = 1.0f;
	if ((Object.x > (this->location.x - halfSize)) && (Object.x < (this->location.x + halfSize)))
		if ((Object.y > (this->location.y - halfSize)) && (Object.y < (this->location.y + halfSize)))
			if ((Object.z > (this->location.z - halfSize)) && (Object.z < (this->location.z)))
				return true;

	return false;
}

bool TriggerLocation::CheckCollisionCubeZN(glm::vec3 Object)
{
	const float halfSize = 1.0f;
	if ((Object.x > (this->location.x - halfSize)) && (Object.x < (this->location.x + halfSize)))
		if ((Object.y > (this->location.y - halfSize)) && (Object.y < (this->location.y + halfSize)))
			if ((Object.z > (this->location.z)) && (Object.z < (this->location.z + halfSize)))
				return true;

	return false;
}
