#ifndef PLAYERCONTROLLERMOVERIGHT_H
#define PLAYERCONTROLLERMOVERIGHT_H

#include "../../Expedition Engine/Game Object/GameObject.h"
#include <stdio.h>
#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_Color.h"
#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_ColorLight.h"
#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_Texture.h"
#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_TextureLight.h"
#include "../../Expedition Engine/Graphics/Model/Model.h"
#include "../../Expedition Engine\Graphics/DXApplication/d3dUtil.h"
#include "../../Expedition Engine/Graphics/Model/Texture.h"
#include "../../Expedition Engine/Graphics/Model/Managers/TextureManager.h"
#include "../../Expedition Engine/Graphics/Terrain/TerrainModel.h"
#include "../../Expedition Engine/GraphicsScene/GraphicsSceneManager.h"
#include "../../Expedition Engine/GraphicsScene/GraphicsScene.h"
#include "../../Expedition Engine/Camera/Camera.h"

class PlayerControllerMoveRight : public KeyboardInputComponent
{
public:
	PlayerControllerMoveRight()
	{
		currentPosition = new Vector4F();
	}
	~PlayerControllerMoveRight()
	{
		delete currentPosition;
	}

	GraphicsObject_ColorLight* testInstance;
	//GraphicObject_TextureLight* testInstance2;
	int sideLen;
	TerrainModel* terrain;

	GraphicsObject_ColorLight* testBox;
	GraphicsObject_ColorLight* testSphere;
	GraphicsObject_TextureLight* testTank;

private:
	Vector4F* currentPosition;
	

	void OnKeyPressed() override
	{
		//*currentPosition += Vector4F(0.01f, 0.0f, 0.0f, 0.0f);
		//testBox->SetWorld(Matrix4F(TRANS, *currentPosition));


		//testBox->SetColor(Colors::Red);
		//testBox->SetMaterial(Colors::Blue, Colors::Blue, Vector4F(1, 1, 1, 20));
		//testSphere->SetMaterial(Colors::Blue, Colors::Blue, Vector4F(1, 1, 1, 5));
		////testSphere->StopDrawing();
		//testTank->SetTexture(TextureManager::Get(TextureName::DuckweedTexture));
	}

	void OnKeyHeld() override
	{
		//GraphicsSceneManager::GetCurrentScene()->currentCamera->TurnLeftRight(-.005f);
		//GraphicsSceneManager::GetCurrentScene()->currentCamera->updateCamera();
		for (int i = 0; i < sideLen*sideLen*sideLen; i++) {
			Matrix4F world = (testInstance->GetWorldUpdate(i) * Matrix4F(TRANS, Vector4F(2, 0, 0, 1))).TransposeCopy();
			int test = (i % (sideLen*sideLen)) / sideLen;
			world[f13] = terrain->BarycentrifyHeight(Vector4F(world[f12], world[f13], world[f14], 1)) + (test * 2);
			testInstance->SetWorld(world, i);
		
			//world = (testInstance2->GetWorld(i) * Matrix4F(TRANS, Vector4F(2, 0, 0, 1))).TransposeCopy();
			//test = (i % (sideLen*sideLen)) / sideLen;
			//world[f13] = terrain->BarycentrifyHeight(Vector4F(world[f12], world[f13], world[f14], 1)) + (test * 2);
			//testInstance2->SetWorld(world, i);
		}

	}
	void OnKeyReleased() override
	{
		//testBox->SetColor(Colors::Purple);
		//testBox->SetMaterial(Colors::Green, Colors::Green, Vector4F(1, 1, 1, 20));
		//testSphere->SetMaterial(Colors::Green, Colors::Green, Vector4F(1, 1, 1, 5));
		//testTank->SetTexture(TextureManager::Get(TextureName::DanceFloorTexture));
	}	//

};

#endif // !PLAYERCONTROLLERMOVERIGHT_H