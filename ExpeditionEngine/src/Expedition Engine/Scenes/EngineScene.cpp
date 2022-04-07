#include "EngineScene.h"

#include "Commands/SceneCommand.h"
#include "SceneManagerAttorney.h"

#include "../Scene Components/Input/Manager/InputManagerAttorney.h"
#include "../Scene Components/Collision/Manager/CollisionSystemAttorney.h"

#include "../Time/SceneTimeManagerAttorney.h"

#include "SceneAttorney.h"

EngineScene::EngineScene()
	:alarmManager(timeManager),
	particleEmitterManager(timeManager, NumberOfParticleBursts)
{
}

EngineScene::~EngineScene()
{
	ShutDownManagers();
}

void EngineScene::ExecuteUpdateStep()
{
	ExecuteCommandsInQueue();

	SceneTimeManagerAttorney::SceneControl::ProcessTime(timeManager);

	alarmManager.ProcessAlarms(timeManager.GetCurrentSceneTime());

	particleEmitterManager.ProcessParticleBursts(timeManager.GetCurrentSceneTime());

	mouseInputManager.ProcessMouseInput();

	keyboardInputManager.ProcessKeyboardInput();

	updateManager.ProcessUpdateCalls();

	collisionManager.ProcessCollisions();
}

void EngineScene::Synchronize()
{
	cameraManager.Synchronize();
}

void EngineScene::Sanitize()
{
	while (commandQueue.GetSize() > 0)
	{
		pTempCommand = commandQueue.Pop();
		pTempCommand->RecycleCommand();
	}
}

void EngineScene::FirstTimeSetUp(const SceneName & sceneName)
{
	cameraManager.Initialize(sceneName);
	//buttonManager.Initialize(sceneName);
}

void EngineScene::Initialize()
{
	SceneAttorney::EngineSceneControls::EngineIntitialization(pUserScene, this);
	SceneAttorney::EngineSceneControls::SceneInitialize(pUserScene);
	ExecuteCommandsInQueue();
}

void EngineScene::Start()
{
	SceneTimeManagerAttorney::SceneControl::StartTime(timeManager);
	InputManagerAttorney::EngineSceneControl::UpdateManagerBindings(mouseInputManager);
	InputManagerAttorney::EngineSceneControl::UpdateManagerBindings(keyboardInputManager);
	CollisionSystemAttorney::EngineSceneControl::SetCurrentCollisionManager(collisionManager);
	
	SceneAttorney::EngineSceneControls::SceneStart(pUserScene);

	isUserSceneActive = true;
}

void EngineScene::Stop()
{
	SceneTimeManagerAttorney::SceneControl::StopTime(timeManager);

	SceneAttorney::EngineSceneControls::SceneStop(pUserScene);

	ExecuteCommandsInQueue();

	isUserSceneActive = false;
}

void EngineScene::ShutDown()
{
	SceneAttorney::EngineSceneControls::SceneShutDown(pUserScene);

	//Just in case someone submitted a registration reqeuest on the last frame, process all of the commands
	ExecuteCommandsInQueue();

	//Tell every registered game object that the scene is ending
	gameObjectManager.ForceAllGameObjectsToExitScene();

	//Now execute all of the commands again to cleanly deregister all gameobjects 
	ExecuteCommandsInQueue();
}

void EngineScene::InsertCommand(SceneCommand * const pCommand)
{
	commandQueue.Push(pCommand);
}

void EngineScene::ExecuteCommandsInQueue()
{
	while (commandQueue.GetSize() > 0)
	{
		pTempCommand = commandQueue.Pop();
		pTempCommand->Execute(this);
		pTempCommand->RecycleCommand();
	}
}

void EngineScene::SetUserScene(Scene * pInitUserScene)
{
	pUserScene = pInitUserScene;
}

Scene * EngineScene::GetUserScene()
{
	return pUserScene;
}

void EngineScene::DeleteUserScene()
{
	delete pUserScene;
	pUserScene = nullptr;
}

bool EngineScene::IsActive()
{
	return isUserSceneActive;
}

void EngineScene::ShutDownManagers()
{
	cameraManager.ShutDown();
}
