#include "SceneTest.h"
#include "../../Expedition Engine/GraphicsScene/GraphicsSceneManager.h"
#include "../../Expedition Engine/Scenes/SceneManager.h"
#include "../../Expedition Engine/Graphics/Model/Model.h"
#include "../../Expedition Engine/Graphics/Model/Managers/ModelManager.h"
//#include "../../Expedition Engine\Graphics/DXApplication/d3dUtil.h"
#include "../../Expedition Engine/Graphics/Model/Managers/TextureManager.h"

#include "../../Expedition Engine/Scene Components/Input/Manager/InputManager.h"
#include"../../Expedition Engine/Graphics/Sprites/Manager/SpriteFontManager.h"
#include "../../Expedition Engine/Graphics/Image/ImageManager.h"
#include "../../Expedition Resources/FontSettings.h"

SceneTest::SceneTest()
	: Scene(SceneName::BouncyBalls), planeController(sceneName), cameraController(sceneName),
	ballManager(sceneName)
	//spriteString(sceneName, SpriteFontManager::Get(FontName::Font1), "Hello World", 50, 50),
	//sceneSwapperButton(sceneName, ImageManager::Get(ImageName::TestImg1), ImageManager::Get(ImageName::TestImg1)->pImageRect)
{

	sceneSwapper.sceneToSwapTo = SceneName::SceneForest;
	//sceneSwapper2.sceneToSwapTo = SceneName::Scene3;

	

	//sceneSwapperButton.sceneToSwapTo = SceneName::Scene2;
	//sceneSwapperButton.SetPosition(100, 400);
}

SceneTest::~SceneTest()
{
}

void SceneTest::SceneInitialize()
{
	cameraController.EnterScene(sceneName);
	planeController.EnterScene(sceneName);
	ballManager.EnterScene(sceneName);

	sceneSwapper.RegisterForOnPressed(sceneName, Input::Number2);
	//sceneSwapper2.RegisterForOnPressed(sceneName, Input::Number3);

	

	SceneManager::GetCurrentPerspectiveCamera(sceneName)->SetOrientAndPosition(Vector4F(0, 1, 0, 0), Vector4F(0, -60, 0, 0), Vector4F(-99, -50, -99, 1));
	SceneManager::GetCurrentPerspectiveCamera(sceneName)->Update();

	//GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->UpdateDirectionLight(0, Vector4F(0, -1, -1));

	Vector4F amb(0.1f, 0.1f, 0.1f, 1.0f);
	Vector4F diff(0.1f, 0.1f, 0.1f, 1.0f);
	Vector4F spec(0.1f, 0.1f, 0.1f, 0.2f);

	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->UpdateDirectionLight(0, Vector4F(0, -1, -1), amb, diff, spec);

	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->InitializeDirectionalLightShadow(0, 2048, Vector4F(0, 0, 0, 1), 200);
	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->EnableDirectionLightShadows(0, sceneName);

	//sceneSwapperButton.StartDrawing(sceneName);
}

void SceneTest::SceneStart()
{
	InputManager::Bind(Input::Keyboard::Number2, InputActions::SwapScene);
	//spriteString.StartDrawing();
}

void SceneTest::SceneStop()
{
	//spriteString.StopDrawing();
}

void SceneTest::SceneShutDown()
{
	cameraController.ExitScene();
	planeController.ExitScene();
	ballManager.ExitScene();
	sceneSwapper.DeregisterFromOnPressed();
}
