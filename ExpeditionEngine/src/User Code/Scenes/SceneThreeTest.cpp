#include "SceneThreeTest.h"

#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_Color.h"
#include "../../Expedition Engine/Graphics/Model/Managers/ModelManager.h"

#include "../../Expedition Engine/Camera/Camera.h"
#include "../../Expedition Engine/GraphicsScene/GraphicsSceneManager.h"
#include "../../Expedition Engine/Graphics/Model/Managers/TextureManager.h"

SceneThreeTest::SceneThreeTest()
	: Scene(SceneName::Scene3), partEmitter(sceneName, 20, 10, 5)
{
	sceneSwapper.sceneToSwapTo = SceneName::Scene1;
	sceneSwapper2.sceneToSwapTo = SceneName::Scene2;

	//GraphicsObjectManager::AquireGraphicsObject(pColorChangingSphere, Scene3, ModelManager::Get(ModelName::TreeModel), 1);
	//TODO: SARA NEEDS TO FIX THIS

	randomColorAlarm.testInstance = pColorChangingSphere;
	randomColorAlarm.timeBetweenAlarms = secondsBetweenSphereColorChange;
	sceneName = SceneName::Scene3;

	//partEmitter.SetEmitterTypeTexture(ModelManager::Get(ModelName::SphereModel), TextureManager::Get(TextureName::DuckweedTexture));
	//partEmitter.SetPosition(Vector4F(0, 0, 0, 1));
}

void SceneThreeTest::SceneInitialize()
{
	GraphicsSceneManager::GetScene(Scene3)->currentCamera->setOrientAndPosition(Vector4F(0.0f, 1.0f, 0.0f, 0.0f), Vector4F(0.0f, 0.0f, 0.0f, 0.0f), Vector4F(0.0f, 20.0f, 30.0f, 1.0f));
	GraphicsSceneManager::GetScene(Scene3)->currentCamera->updateCamera();

	sceneSwapper.RegisterForOnPressed(sceneName, Input::Number1);
	sceneSwapper2.RegisterForOnPressed(sceneName, Input::Number2);

	pColorChangingSphere->StartDrawing();
	
	//pColorChangingSphere->SetWorld(Matrix4F(TRANS, Vector4F(400, 250, 400, 1)), 0);
	randomColorAlarm.SetAlarm(sceneName, secondsBetweenSphereColorChange);
}

void SceneThreeTest::SceneStart()
{
	InputManager::Bind(Input::Keyboard::Number1, InputActions::SwapScene);

	//partEmitter.RegisterToScene();
}

void SceneThreeTest::SceneStop()
{
	//partEmitter.DeregisterFromScene();
}

void SceneThreeTest::SceneShutDown()
{
	pColorChangingSphere->StopDrawing();
	sceneSwapper.DeregisterFromOnPressed();
	randomColorAlarm.StopAlarm();
}

SceneThreeTest::~SceneThreeTest()
{
	//GraphicsObjectManager::ReleaseGraphicsObject(pColorChangingSphere);
	//TODO: SARA NEEDS TO FIX THIS
}