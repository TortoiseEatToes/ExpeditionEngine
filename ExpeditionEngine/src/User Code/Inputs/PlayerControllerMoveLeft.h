#ifndef PLAYERCONTROLLERMOVELEFT_H
#define PLAYERCONTROLLERMOVELEFT_H

#include "../../Expedition Engine/Scene Components/Game Object/GameObject.h"
#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_ColorLight.h"
#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_Color.h"
#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_TextureLight.h"
#include "../../Expedition Engine/Math/Matrix/Matrix4F.h"
#include "../../Expedition Engine/Math/Vector/Vector4F.h"
#include "../../Expedition Engine/Graphics/Terrain/TerrainModel.h"
#include "../../Expedition Engine/GraphicsScene/GraphicsSceneManager.h"
#include "../../Expedition Engine/GraphicsScene/GraphicsScene.h"
#include "../../Expedition Engine/Camera/Camera.h"
#include <stdio.h>

class PlayerControllerMoveLeft : public KeyboardInputComponent
{
public:
	GraphicsObject_ColorLight* testInstance;
	//GraphicObject_TextureLight* testInstance2;
	int sideLen;
	TerrainModel* terrain;
private:
	void OnKeyPressed() override
	{

	}
	void OnKeyHeld() override
	{
		//GraphicsSceneManager::GetCurrentScene()->currentCamera->TurnLeftRight(.005f);
		//GraphicsSceneManager::GetCurrentScene()->currentCamera->updateCamera();

		for (int i = 0; i < sideLen*sideLen*sideLen; i++) {
			Matrix4F world = (testInstance->GetWorldUpdate(i) * Matrix4F(TRANS, Vector4F(-2, 0, 0, 1))).TransposeCopy();
			int test = (i % (sideLen*sideLen)) / sideLen;
			world[f13] = terrain->BarycentrifyHeight(Vector4F(world[f12], world[f13], world[f14], 1)) + (test * 2);
			testInstance->SetWorld(world, i);
		
			//world = (testInstance2->GetWorld(i) * Matrix4F(TRANS, Vector4F(-2, 0, 0, 1))).TransposeCopy();
			//test = (i % (sideLen*sideLen)) / sideLen;
			//world[f13] = terrain->BarycentrifyHeight(Vector4F(world[f12], world[f13], world[f14], 1)) + (test * 2);
			//testInstance2->SetWorld(world, i);
		}
	}
	void OnKeyReleased() override
	{

	}

};

#endif // !PLAYERCONTROLLERMOVELEFT_H