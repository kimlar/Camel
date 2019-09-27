#pragma once

#include <glm/glm.hpp>

class TriggerLocation
{
public:
	TriggerLocation(glm::vec3 location);
	~TriggerLocation();

	bool CheckTrigger(glm::vec3 Object);

	bool CheckCollisionCubeXP(glm::vec3 Object);
	bool CheckCollisionCubeXN(glm::vec3 Object);
	bool CheckCollisionCubeYP(glm::vec3 Object);
	bool CheckCollisionCubeYN(glm::vec3 Object);
	bool CheckCollisionCubeZP(glm::vec3 Object);
	bool CheckCollisionCubeZN(glm::vec3 Object);

	glm::vec3 location;
};
