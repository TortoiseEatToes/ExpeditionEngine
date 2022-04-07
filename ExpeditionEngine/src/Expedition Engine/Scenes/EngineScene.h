#pragma once

#include "../Scene Components/Game Object/Manager/GameObjectManager.h"
#include "../Scene Components/Update/Manager/UpdateManager.h"
#include "../Scene Components/Alarm/Manager/AlarmManager.h"
#include "../Scene Components/Input/Mouse/Manager/MouseInputManager.h"
#include "../Scene Components/Input/Keyboard/Manager/KeyboardInputManager.h"
#include "../Time/SceneTimeManager.h"
#include "../Scene Components/Collision/Manager/CollisionManager.h"
#include "../UI/ButtonManager.h"
#include "../Camera/CameraManager.h"

#include "../Scene Components/Particle Emitter/ParticleEmitterManager.h"

#include "../Containers/Queue.h"

#include "../../Expedition Resources/SceneSettings.h"

class SceneCommand;

class Camera;

class Scene;

class EngineScene
{
public:
	EngineScene();
	EngineScene(const EngineScene& other) = delete;
	EngineScene& operator= (const EngineScene& other) = delete;
	~EngineScene();


	void ExecuteUpdateStep();

	void Synchronize();

	void Sanitize();

	void FirstTimeSetUp(const SceneName& sceneName);
	void Initialize();
	void Start();
	void Stop();
	void ShutDown();

	GameObjectManager& GetGameObjectManager() { return gameObjectManager; }
	SceneTimeManager& GetTimeManager() { return timeManager; }
	AlarmManager& GetAlarmManager() { return alarmManager; }
	MouseInputManager& GetMouseInputManager() { return mouseInputManager; }
	KeyboardInputManager& GetKeyboardInputManager() { return keyboardInputManager; }
	UpdateManager& GetUpdateManager() { return updateManager; }
	CollisionManager& GetCollisionManager() { return collisionManager; }
	//ButtonManager& GetButtonManager();
	ParticleEmitterManager& GetParticleEmitterManager() { return particleEmitterManager; }
	CameraManager& GetCameraManager() { return cameraManager; }
	const CameraDataManager& GetCameraDataManager() const { return cameraManager.GetCameraDataManager(); }

	void InsertCommand(SceneCommand* const pCommand);
	void ExecuteCommandsInQueue();

	void SetUserScene(Scene* pInitUserScene);
	Scene* GetUserScene();

	void DeleteUserScene();

	bool IsActive();

private:
	void ShutDownManagers();

	GameObjectManager gameObjectManager;
	SceneTimeManager timeManager;
	AlarmManager alarmManager;
	MouseInputManager mouseInputManager;
	KeyboardInputManager keyboardInputManager;
	UpdateManager updateManager;
	CollisionManager collisionManager;
	//ButtonManager buttonManager;
	ParticleEmitterManager particleEmitterManager;
	CameraManager cameraManager;

	Queue<SceneCommand*> commandQueue;
	SceneCommand* pTempCommand = nullptr;

	Scene* pUserScene = nullptr;
	bool isUserSceneActive = false;
};