#include "SceneTwoTest.h"



//#include "../../Expedition Engine/Graphics/DXApplication/d3dUtil.h"
#include "../../Expedition Engine/Graphics/Model/Managers/ModelManager.h"
#include "../../Expedition Engine/Graphics/Terrain/TerrainObjectManager.h"
#include "../../Expedition Engine/Graphics/Terrain/TerrainModel.h"
#include "../../Expedition Engine/Graphics/Model/Managers/TextureManager.h"
#include "../../Expedition Engine/Graphics/Model/Managers/ModelManager.h"
#include "../../Expedition Engine/Graphics/Image/ImageManager.h"
#include "../../Expedition Engine/Graphics/Image/Image.h"
#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_TextureLight.h"
#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_ColorLight.h"

#include "../../Expedition Engine/GraphicsScene/GraphicsSceneManager.h"
#include "../../Expedition Engine/GraphicsScene/GraphicsScene.h"
#include "../../Expedition Engine/Camera/Camera.h"

#include "../../Expedition Engine/Tools/Colors.h"

#include <winuser.h>

//#include "../../Expedition Engine/Graphics/DXApplication/d3dUtil.h"

SceneTwoTest::SceneTwoTest() : Scene(Scene2), spriteController(sceneName), cameraController(sceneName), pe(sceneName, 5 , 1.0f, 20), particleSwapper(sceneName, ImageManager::Get(ImageName::TestImg4), ImageManager::Get(ImageName::TestImg4)->pImageRect)
{
	sceneSwapper.sceneToSwapTo = SceneName::Scene3;
	sceneSwapper2.sceneToSwapTo = SceneName::Scene1;
	//terrain = new GraphicObject_ColorLight(sceneName, ModelManager::Get(ModelName::SkyModel));

	pe.SetEmitterTypeTexture(ModelManager::Get(ModelName::TankModel), TextureManager::Get(TextureName::FlameTexture));

	particleSwapper.SetPosition(400, 200);

	particleSwapper.pe = &pe;
	particleSwapper.model = ModelManager::Get(ModelName::TankModel);
	particleSwapper.sceneName = sceneName;
	particleSwapper.texture = TextureManager::Get(TextureName::FlameTexture);
	
}

void SceneTwoTest::SceneInitialize()
{
	cameraController.EnterScene(sceneName);
	sceneSwapper.RegisterForOnPressed(sceneName, Input::Number3);
	sceneSwapper2.RegisterForOnPressed(sceneName, Input::Number1);
	//spriteController.RegisterIntoScene(sceneName);

	//terrain->SetTexture(TextureManager::Get(TextureName::DanceFloorTexture));
	//terrain->SetMaterial(Colors::White, Colors::White, Colors::White);
	//terrain->SetWorld(Matrix4F(IDENTITY));

	GraphicsSceneManager::GetScene(sceneName)->currentCamera->setOrientAndPosition(Vector4F(0, 1, 0, 0), Vector4F(0, 0, 0, 1), Vector4F(0, 0, 200, 1));
	GraphicsSceneManager::GetScene(sceneName)->currentCamera->updateCamera();

	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->UpdateDirectionLight(0, Vector4F(0, -1, -1));
	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->UpdateSpotLight(0, Vector4F(0,100,0, 1), Vector4F(0,-1,0), Vector4F(0,0,1), 2000, 64);
	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->UpdatePointLight(0,Vector4F(200,0,0,1), Vector4F(0,0,1), 500);

	pe.RegisterToScene();
	pe.SetPosition(Vector4F(0, 0, 0, 1));
	pe.SetColor(Colors::Violet);
}

void SceneTwoTest::SceneStart()
{
	
	//terrain->StartDrawing();
	
	
	//spriteController.RegisterIntoScene(sceneName);
	//sceneSwapper.RegisterForOnPressed(sceneName, Input::Number3);

	
	//POINT p;
	//GetCursorPos(&p);

	//InputManager::Bind(Input::Keyboard::Number3, InputActions::SwapScene);

	particleSwapper.StartDrawing(sceneName);
}

void SceneTwoTest::SceneStop()
{
	//terrain->StopDrawing();
	particleSwapper.StopDrawing();

}

void SceneTwoTest::SceneShutDown()
{
	//spriteController.DeregisterFromScene();
	//cameraController.DeregisterFromScene();
	//sceneSwapper.DeregisterFromOnPressed();

	pe.DeregisterFromScene();
}

SceneTwoTest::~SceneTwoTest()
{
	
	//delete terrain;
}