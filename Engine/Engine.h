#pragma once

// Standard C++
#include <vector>

// Engine
#include "Window.h"
#include "Camera.h"
#include "UIMouseCursor.h"
#include "UIButton.h"
#include "CollisionCube.h"
#include "CollisionFloor.h"
#include "CollisionCeiling.h"
#include "TriggerLocation.h"
#include "UIText.h"

// Game
#include "../StoneFloor.h"
#include "../StoneWall.h"
#include "../StoneCeiling.h"
#include "../WoodBlock.h"
#include "../DiceWall.h"
#include "../Suzanne.h"
#include "../WindowGlass.h"
#include "../Cylinder.h"
#include "../LightMap.h"
#include "../ShadowMapPointLight.h"
#include "../SuzanneRotation.h"
#include "../Billboard.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Run();

	Window* window;
	Camera* camera;
	UIMouseCursor* uiMouseCursor;
	UIButton* uiButton;
	UIText* uiText;

	bool showMenu;
	bool prevMenuState;


	//-----------------------------
	std::vector<StoneFloor*> vStoneFloor;
	std::vector<StoneWall*> vStoneWall;
	std::vector<StoneCeiling*> vStoneCeiling;
	std::vector<WoodBlock*> vWoodBlock;
	std::vector<TriggerLocation*> vTriggerLocation;
	std::vector<DiceWall*> vDiceWall;
	std::vector<Suzanne*> vSuzanne;
	std::vector<WindowGlass*> vWindowGlass;
	std::vector<Cylinder*> vCylinder;
	std::vector<LightMap*> vLightMap;
	std::vector<ShadowMapPointLight*> vShadowMapPointLight;
	std::vector<SuzanneRotation*> vSuzanneRotation;
	std::vector<Billboard*> vBillboard;

};
