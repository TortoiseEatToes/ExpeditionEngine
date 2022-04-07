#include "PlayerController.h"

#include "../../Expedition Engine/Scene Components/Input/Manager/InputManager.h"

#include "../../Expedition Engine/Camera/Camera.h"
//#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_Color.h"
//#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_ColorLight.h"
//#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_Texture.h"
//#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_TextureLight.h"
//#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_Sprite.h"
#include "../../Expedition Engine/Graphics/Model/Model.h"
#include "../../Expedition Engine/Graphics/Model/Texture.h"
#include "../../Expedition Engine/Graphics/Model/Managers/ModelManager.h"
#include "../../Expedition Engine/Graphics/Model/Managers/TextureManager.h"
#include "../../Expedition Engine/Graphics/Terrain/TerrainObjectManager.h"
//#include "../../Expedition Engine\Graphics/DXApplication/d3dUtil.h"

#include "../../Expedition Engine/Graphics/Image/ImageManager.h"
#include "../../Expedition Resources/LayerSettings.h"

#include "../../Expedition Engine/GraphicsScene/GraphicsSceneManager.h"

#include "../../Expedition Engine/Engine/ExpeditionEngine.h"

#include "../../Expedition Engine/Graphics/Image/Image.h"

#include "../../Expedition Engine/Graphics/Sprites/Manager/SpriteFontManager.h"
#include "../../Expedition Engine/Graphics/Sprites/SpriteString.h"
#include "../../Expedition Resources/FontSettings.h"

#include "../../Expedition Engine/Graphics/Model/Managers/TextureManager.h"

PlayerController::PlayerController(const SceneName& startingScene)
	: GameObject(startingScene)
{	
	//GraphicsObjectManager::AquireGraphicObject(skyBox, registeredScene, ModelManager::Get(ModelName::SkyModel), 1);
	//skyBox->SetTexture(TextureName::DanceFloorTexture);
	//skyBox->SetWorld(Matrix4F(IDENTITY));


	//GraphicsObjectManager::AquireGraphicsObject(testInstanced, registeredScene, ModelManager::Get(ModelName::CubeModel), sideLen * sideLen * sideLen);
	//TODO: SARA NEEDS TO FIX THIS

	for (int i = 0; i < sideLen; i++)
	{
		for (int j = 0; j < sideLen; j++)
		{
			for (int k = 0; k < sideLen; k++)
			{

				Vector4F color = Vector4F(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
					static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
					static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1);


				testInstanced->SetWorld((Matrix4F(TRANS, Vector4F(static_cast<float>(i * 2), static_cast<float>(j * 2), static_cast<float>(k * 2), 1))* Matrix4F(SCALE, 1)).TransposeCopy(), (i*sideLen*sideLen) + (j*sideLen) + k);
				testInstanced->SetMaterial(color, color, Vector4F(.5, .5, .5, static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), (i * sideLen*sideLen) + (j * sideLen) + k);
			}
		}
	}



	//GraphicsObjectManager::AquireGraphicObject(terrain, registeredScene, TerrainObjectManager::Get(TerrainName::BasinTerrain));
	//TODO: SARA NEEDS TO FIX THIS
	terrain->SetTexture(TextureManager::Get(TextureName::DuckweedTexture));
	terrain->SetMaterial(Colors::Green, Colors::Green, Vector4F(1, 1, 1, 5));
	terrain->SetWorld(Matrix4F(IDENTITY), 0);
}

PlayerController::~PlayerController()
{
	//GraphicsObjectManager::ReleaseGraphicObject(terrain);
	//GraphicsObjectManager::ReleaseGraphicsObject(testInstanced);
	//TODO: SARA NEEDS TO FIX THIS
}

void PlayerController::OnSceneEnter()
{
	GraphicsSceneManager::GetScene(Scene1)->currentCamera->setOrientAndPosition(Vector4F(0, 1, 0, 0), Vector4F(0, 0, 0, 0), Vector4F(300, 200 , 600, 1));
	GraphicsSceneManager::GetScene(Scene1)->currentCamera->updateCamera();
	
	skyBox->StartDrawing();

	testInstanced->StartDrawing();

	terrain->StartDrawing();

	GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->UpdateDirectionLight(0, Vector4F(0, -1, -1));
	GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->UpdateSpotLight(0, Vector4F(10, 0, 0, 1), Vector4F(-1, 0, 0), Vector4F(1, 0, 0, 1), 200, 4);

	playerControllerMoveBackward.RegisterForAll(GetRegisteredScene(), Input::LetterKeyS);
	playerControllerMoveBackward.testInstance = testInstanced;
	playerControllerMoveBackward.sideLen = sideLen;
	playerControllerMoveBackward.terrain = terrain->GetTerrainModel();

	
	playerControllerMoveForward.RegisterForAll(GetRegisteredScene(), Input::LetterKeyW);
	playerControllerMoveForward.testInstance = testInstanced;
	playerControllerMoveForward.sideLen = sideLen;
	playerControllerMoveForward.terrain = terrain->GetTerrainModel();

	playerControllerMoveLeft.RegisterForAll(GetRegisteredScene() ,Input::LetterKeyA);
	playerControllerMoveLeft.testInstance = testInstanced;
	playerControllerMoveLeft.sideLen = sideLen;
	playerControllerMoveLeft.terrain = terrain->GetTerrainModel();

	playerControllerMoveRight.RegisterForAll(GetRegisteredScene(), Input::LetterKeyD);
	playerControllerMoveRight.testInstance = testInstanced;
	playerControllerMoveRight.sideLen = sideLen;
	playerControllerMoveRight.terrain = terrain->GetTerrainModel();

	playerControllerQuitGame.RegisterForAll(GetRegisteredScene(), Input::Escape);

}

void PlayerController::OnSceneExit()
{

	playerControllerMoveBackward.DeregisterFromAll();
	playerControllerMoveForward.DeregisterFromAll();
	playerControllerMoveLeft.DeregisterFromAll();
	playerControllerMoveRight.DeregisterFromAll();
	playerControllerQuitGame.DeregisterFromAll();

	terrain->StopDrawing();
	testInstanced->StopDrawing();
	skyBox->StopDrawing();

}
