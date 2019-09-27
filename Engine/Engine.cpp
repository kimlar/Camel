#include "Engine.h"

Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::Run()
{
	window = new Window();
	bool run = window->Create();

	uiMouseCursor = new UIMouseCursor(window);
	uiMouseCursor->Create();

	camera = new Camera(window);
	camera->Create();

	uiButton = new UIButton(window);
	uiButton->Create(glm::vec3(0.0f, 0.0f, 0.0f));

	uiText = new UIText();
	uiText->Create("FPS:", 680, 580, 12); // TODO: Fix correct positioning, because now this does not reflect real monitor coordinates.
	
	// Stone floor
	for (int y = -5; y < 5; y++)
	{
		for (int x = -5; x < 5; x++)
		{
			vStoneFloor.push_back(new StoneFloor(camera));
			vStoneFloor.back()->Create(glm::vec3((float)(x*2), 0.0f, (float)(y*2)));
		}
	}
	
	// Stone wall
	for (int y = 0; y < 10; y++)
	{
		for (int i = -5; i < 5; i++)
		{
			vStoneWall.push_back(new StoneWall(camera));
			vStoneWall.back()->Create(glm::vec3((float)(i * 2), (float)(y * 2), -10.0f));
		}
		for (int i = -5; i < 5; i++)
		{
			vStoneWall.push_back(new StoneWall(camera));
			vStoneWall.back()->Create(glm::vec3((float)(i * 2), (float)(y * 2), 10.0f));
		}
		for (int i = -5; i < 5; i++)
		{
			vStoneWall.push_back(new StoneWall(camera));
			vStoneWall.back()->Create(glm::vec3(-10.0f, (float)(y * 2), (float)(i * 2)));
		}
		for (int i = -5; i < 5; i++)
		{
			vStoneWall.push_back(new StoneWall(camera));
			vStoneWall.back()->Create(glm::vec3(10.0f, (float)(y * 2), (float)(i * 2)));
		}
	}
		
	// Stone ceiling
	for (int y = -5; y < 5; y++)
	{
		for (int x = -5; x < 5; x++)
		{
			vStoneCeiling.push_back(new StoneCeiling(camera));
			vStoneCeiling.back()->Create(glm::vec3((float)(x * 2), 10.0f, (float)(y * 2)));
		}
	}
	
	vWoodBlock.push_back(new WoodBlock(camera));
	vWoodBlock.back()->Create(glm::vec3(2.0f, 0.0f, 2.0f));
	//
	vWoodBlock.push_back(new WoodBlock(camera));
	vWoodBlock.back()->Create(glm::vec3(4.0f, 2.0f, 2.0f));
	//
	vWoodBlock.push_back(new WoodBlock(camera));
	vWoodBlock.back()->Create(glm::vec3(6.0f, 4.0f, 2.0f));
	//
	vWoodBlock.push_back(new WoodBlock(camera));
	vWoodBlock.back()->Create(glm::vec3(8.0f, 6.0f, 2.0f));
	//
//	vWoodBlock.push_back(new WoodBlock(camera));
//	vWoodBlock.back()->Create(glm::vec3(10.0f, 8.0f, 2.0f));

//	// Trigger
//	vTriggerLocation.push_back(new TriggerLocation(glm::vec3(5.0f, 0.0f, -5.0f)));
	

	// DiceWall
	vDiceWall.push_back(new DiceWall(camera));
	vDiceWall.back()->Create(glm::vec3(-2.0f, 0.0f, -6.0f));

	// Suzanne
	vSuzanne.push_back(new Suzanne(camera));
	vSuzanne.back()->Create(glm::vec3(-4.0f, 2.0f, -4.0f));
	
	// WindowGlass
	vWindowGlass.push_back(new WindowGlass(camera));
	vWindowGlass.back()->Create(glm::vec3(-4.0f, 2.0f, 4.0f));
	
	// Cylinder
	vCylinder.push_back(new Cylinder(camera));
	vCylinder.back()->Create(glm::vec3(4.0f, -1.0f, -3.0f));

	// Cylinder
	vCylinder.push_back(new Cylinder(camera));
	vCylinder.back()->Create(glm::vec3(4.0f, 1.0f, -3.0f));

	// Cylinder
	vCylinder.push_back(new Cylinder(camera));
	vCylinder.back()->Create(glm::vec3(4.0f, 3.0f, -3.0f));

	// Cylinder
	vCylinder.push_back(new Cylinder(camera));
	vCylinder.back()->Create(glm::vec3(4.0f, 5.0f, -3.0f));

	// Cylinder
	vCylinder.push_back(new Cylinder(camera));
	vCylinder.back()->Create(glm::vec3(4.0f, 7.0f, -3.0f));
	

	// LightMap
	//vLightMap.push_back(new LightMap(camera));
	//vLightMap.back()->Create(glm::vec3(5.0f, -2.0f, 2.0f));
	
	// ShadowMapPointLight
	//vShadowMapPointLight.push_back(new ShadowMapPointLight(camera));
	//vShadowMapPointLight.back()->Create(glm::vec3(5.0f, -2.0f, 2.0f));

	// SuzanneRotation
	//vSuzanneRotation.push_back(new SuzanneRotation(camera));
	//vSuzanneRotation.back()->Create(glm::vec3(5.0f, -2.0f, 2.0f));

	// Billboard
	vBillboard.push_back(new Billboard(camera));
	vBillboard.back()->Create(glm::vec3(2.0f, 1.0f, -3.0f));

	while (run = window->Update())
	{
		// Toggle menu ---- TODO: Move this inside a Menu class
		if (window->keys[GLFW_KEY_ESCAPE] == GLFW_PRESS && prevMenuState == false)
		{
			showMenu = !showMenu;
			prevMenuState = true;
			
			if (showMenu)
				window->ShowMouseCursor();
			else
				window->HideMouseCursor();
		}
		if (window->keys[GLFW_KEY_ESCAPE] == GLFW_RELEASE)
		{
			prevMenuState = false;
		}

		// Camera
		camera->Update();
				

		// Check collision against stone floor
		for (int i = 0; i < vStoneFloor.size(); i++)
		{
			if (CheckCollisionFloor(camera->position, vStoneFloor[i]->position))
			{
				camera->position.y = vStoneFloor[i]->position.y + 1.0f;
				camera->ResetJumping();
			}
		}
		// Check collision against stone wall
		for (int i = 0; i < vStoneWall.size(); i++)
		{
			if (CheckCollisionCubeXP(camera->position, vStoneWall[i]->position))
			{
				camera->position.x = vStoneWall[i]->position.x - 1.0f - cameraMinDistance;
			}
			if (CheckCollisionCubeXN(camera->position, vStoneWall[i]->position))
			{
				camera->position.x = vStoneWall[i]->position.x + 1.0f + cameraMinDistance;
			}
			if (CheckCollisionCubeYP(camera->position, vStoneWall[i]->position))
			{
				camera->position.y = vStoneWall[i]->position.y - 1.0f - cameraMinDistance;
				camera->CollidedWithCeiling();
			}
			if (CheckCollisionCubeYN(camera->position, vStoneWall[i]->position))
			{
				camera->position.y = vStoneWall[i]->position.y + 1.0f + cameraMinDistance + cameraHeight;
				if(camera->jumpVelocity < 0)
					camera->ResetJumping();
			}
			if (CheckCollisionCubeZP(camera->position, vStoneWall[i]->position))
			{
				camera->position.z = vStoneWall[i]->position.z - 1.0f - cameraMinDistance;
			}
			if (CheckCollisionCubeZN(camera->position, vStoneWall[i]->position))
			{
				camera->position.z = vStoneWall[i]->position.z + 1.0f + cameraMinDistance;
			}
		}
		// Check collision against stone ceiling
		for (int i = 0; i < vStoneCeiling.size(); i++)
		{
			if (CheckCollisionCeiling(camera->position, vStoneCeiling[i]->position))
			{
				camera->position.y = vStoneCeiling[i]->position.y - 1.0f - cameraMinDistance;
				camera->CollidedWithCeiling();
			}
		}


		// Check collision against stone wall
		for (int i = 0; i < vWoodBlock.size(); i++)
		{
			if (CheckCollisionCubeXP(camera->position, vWoodBlock[i]->position))
			{
				camera->position.x = vWoodBlock[i]->position.x - 1.0f - cameraMinDistance;
			}
			if (CheckCollisionCubeXN(camera->position, vWoodBlock[i]->position))
			{
				camera->position.x = vWoodBlock[i]->position.x + 1.0f + cameraMinDistance;
			}
			if (CheckCollisionCubeYP(camera->position, vWoodBlock[i]->position))
			{
				camera->position.y = vWoodBlock[i]->position.y - 1.0f - cameraMinDistance;
				camera->CollidedWithCeiling();
			}
			if (CheckCollisionCubeYN(camera->position, vWoodBlock[i]->position))
			{
				camera->position.y = vWoodBlock[i]->position.y + 1.0f + cameraMinDistance + cameraHeight;
				if (camera->jumpVelocity < 0)
					camera->ResetJumping();
			}
			if (CheckCollisionCubeZP(camera->position, vWoodBlock[i]->position))
			{
				camera->position.z = vWoodBlock[i]->position.z - 1.0f - cameraMinDistance;
			}
			if (CheckCollisionCubeZN(camera->position, vWoodBlock[i]->position))
			{
				camera->position.z = vWoodBlock[i]->position.z + 1.0f + cameraMinDistance;
			}
		}

		//for (int i = 0; i < vTriggerLocation.size(); i++)
		//{
		//	if (vTriggerLocation[i]->CheckTrigger(camera->position))
		//	{
		//		window->quit = true;
		//	}
		//}
			

		//
		// Update
		//
		for (int i = 0; i < vStoneFloor.size(); i++)
			vStoneFloor[i]->Update();
		for (int i = 0; i < vStoneWall.size(); i++)
			vStoneWall[i]->Update();
		for (int i = 0; i < vStoneCeiling.size(); i++)
			vStoneCeiling[i]->Update();
		for (int i = 0; i < vWoodBlock.size(); i++)
			vWoodBlock[i]->Update();
		for (int i = 0; i < vDiceWall.size(); i++)
			vDiceWall[i]->Update();
		for (int i = 0; i < vSuzanne.size(); i++)
			vSuzanne[i]->Update();
		for (int i = 0; i < vWindowGlass.size(); i++)
			vWindowGlass[i]->Update();
		//for (int i = 0; i < vLightMap.size(); i++)
		//	vLightMap[i]->Update();
		//for (int i = 0; i < vShadowMapPointLight.size(); i++)
		//	vShadowMapPointLight[i]->Update();
		//for (int i = 0; i < vSuzanneRotation.size(); i++)
		//	vSuzanneRotation[i]->Update();
		for (int i = 0; i < vBillboard.size(); i++)
			vBillboard[i]->Update();
				

		// Handle menu if shown
		if (showMenu)
			uiButton->Update();


		//
		// Render
		//
		window->RenderBegin();

		//==============================================================================================================================
		//
		// Draw stuff
		//
		//==============================================================================================================================

		//
		// Render regular objects first. I.e window-frames (but not the window-glass)
		//
		for (int i = 0; i < vStoneFloor.size(); i++)
			vStoneFloor[i]->Render();
		for (int i = 0; i < vStoneWall.size(); i++)
			vStoneWall[i]->Render();
		for (int i = 0; i < vStoneCeiling.size(); i++)
			vStoneCeiling[i]->Render();
		for (int i = 0; i < vWoodBlock.size(); i++)
			vWoodBlock[i]->Render();
		for (int i = 0; i < vDiceWall.size(); i++)
			vDiceWall[i]->Render();
		for (int i = 0; i < vSuzanne.size(); i++)
			vSuzanne[i]->Render();
		for (int i = 0; i < vCylinder.size(); i++)
			vCylinder[i]->Render();
		//for (int i = 0; i < vLightMap.size(); i++)
		//	vLightMap[i]->Render();
		//for (int i = 0; i < vShadowMapPointLight.size(); i++)
		//	vShadowMapPointLight[i]->Render();
		//for (int i = 0; i < vSuzanneRotation.size(); i++)
		//	vSuzanneRotation[i]->Render();
		for (int i = 0; i < vBillboard.size(); i++)
			vBillboard[i]->Render();
				
		
		//
		// Render Transparency/translucent objects last. I.e window-glass (but not window-frames)
		//
		for (int i = 0; i < vWindowGlass.size(); i++)
			vWindowGlass[i]->Render();

		// Show UI elements (HUD)
		uiText->SetText(window->fpsText);
		uiText->Render();

		// Display menu?
		if (showMenu)
			uiButton->Render();

		window->RenderEnd();
	}

	for (int i = 0; i < vStoneFloor.size(); i++)
		vStoneFloor[i]->Destroy();
	vStoneFloor.clear();

	for (int i = 0; i < vStoneWall.size(); i++)
		vStoneWall[i]->Destroy();
	vStoneWall.clear();

	for (int i = 0; i < vStoneCeiling.size(); i++)
		vStoneCeiling[i]->Destroy();
	vStoneCeiling.clear();

	for (int i = 0; i < vWoodBlock.size(); i++)
		vWoodBlock[i]->Destroy();
	vWoodBlock.clear();

	for (int i = 0; i < vDiceWall.size(); i++)
		vDiceWall[i]->Destroy();
	vDiceWall.clear();
	
	for (int i = 0; i < vSuzanne.size(); i++)
		vSuzanne[i]->Destroy();
	vSuzanne.clear();
	
	for (int i = 0; i < vWindowGlass.size(); i++)
		vWindowGlass[i]->Destroy();
	vWindowGlass.clear();

	for (int i = 0; i < vCylinder.size(); i++)
		vCylinder[i]->Destroy();
	vCylinder.clear();

	//for (int i = 0; i < vLightMap.size(); i++)
	//	vLightMap[i]->Destroy();
	//vLightMap.clear();
	
	//for (int i = 0; i < vShadowMapPointLight.size(); i++)
	//	vShadowMapPointLight[i]->Destroy();
	//vShadowMapPointLight.clear();

	//for (int i = 0; i < vSuzanneRotation.size(); i++)
	//	vSuzanneRotation[i]->Destroy();
	//vSuzanneRotation.clear();
	
	for (int i = 0; i < vBillboard.size(); i++)
		vBillboard[i]->Destroy();
	vBillboard.clear();
	

	//vTriggerLocation.clear();

	uiButton->Destroy();
	delete uiButton;

	uiText->Destroy();
	delete uiText;

	camera->Destroy();
	delete camera;

	uiMouseCursor->Destroy();
	delete uiMouseCursor;

	window->Destroy();
	delete window;
}
