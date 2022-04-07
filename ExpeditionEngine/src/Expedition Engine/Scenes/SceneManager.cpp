#include "SceneManager.h"
#include "../Scene Components/Input/Mouse/MouseInputComponent.h"

#include <assert.h>

SceneManager* SceneManager::pInstance = nullptr;

SceneManager::SceneManager()
{
	currentScene = startingScene;
	//pCurrentScene = &scenesArray[startingScene];
}

Scene * SceneManager::privGetCurrentScene()
{
	return scenesArray[currentScene].GetUserScene();
}

void SceneManager::privProccessSceneCreationAndDeletionCommands()
{
	while (queueCreateScene.GetSize() > 0)
	{
		pTempManagerCommand = queueCreateScene.Pop();
		pTempManagerCommand->Execute();
		delete pTempManagerCommand;
	}

	while (queueDestroyScene.GetSize() > 0)
	{
		pTempSceneDeletionCommand = queueDestroyScene.Pop();
		pTempSceneDeletionCommand->Execute();
		poolDestroyScene.RecycleObject(pTempSceneDeletionCommand);
	}
}

void SceneManager::privProcessSceneChangeCommands()
{
	while (queueChangeScene.GetSize() > 0)
	{
		pTempSceneChangeCommand = queueChangeScene.Pop();
		pTempSceneChangeCommand->Execute();
		poolChangeScene.RecycleObject(pTempSceneChangeCommand);
	}
}

void SceneManager::privDestroyScene(const SceneName& nameOfSceneToDestroy)
{
	pTempSceneDeletionCommand = poolDestroyScene.GetPooledObject();   
	pTempSceneDeletionCommand->Initialize(nameOfSceneToDestroy);
	queueDestroyScene.Push(pTempSceneDeletionCommand);
}

void SceneManager::cmdprivDestroyScene(const SceneName& nameOfSceneToDestroy)
{
	assert(scenesArray[nameOfSceneToDestroy].GetUserScene() != nullptr && "Trying to destroy a scene that does not exist currently");

	scenesArray[nameOfSceneToDestroy].ShutDown();

	GraphicsSceneManagerAttorney::SceneManagerControl::SantitizeScene(nameOfSceneToDestroy);

	scenesArray[nameOfSceneToDestroy].Sanitize();
	
	scenesArray[nameOfSceneToDestroy].DeleteUserScene();
}

void SceneManager::privChangeScene(const SceneName& sceneName)
{
	pTempSceneChangeCommand = poolChangeScene.GetPooledObject();
	pTempSceneChangeCommand->Initialize(sceneName);
	queueChangeScene.Push(pTempSceneChangeCommand);
}

void SceneManager::cmdprivChangeScene(const SceneName& nextSceneName)
{
	scenesArray[currentScene].Stop();

	assert(scenesArray[nextSceneName].GetUserScene() != nullptr);
	currentScene = nextSceneName;

	scenesArray[currentScene].Start();

	GraphicsSceneManagerAttorney::SceneManagerControl::SetCurrentScene(nextSceneName);
}

const CameraData & SceneManager::privGetCurrentPerspectiveCameraData() const
{
	return scenesArray[currentScene].GetCameraDataManager().GetCurrentCameraDataPerspective();
}

const CameraData & SceneManager::privGetCurrentOrthographicCameraData() const
{
	return scenesArray[currentScene].GetCameraDataManager().GetCurrentCameraDataOrthograpic();
}

void SceneManager::privStartFirstScene()
{
	for (int i = 0; i < NumberOfScenes; ++i)
	{
		scenesArray[i].FirstTimeSetUp((SceneName)i);
	}

	while (queueCreateScene.GetSize() > 0)
	{
		pTempManagerCommand = queueCreateScene.Pop();
		pTempManagerCommand->Execute();
		delete pTempManagerCommand;
	}
	assert(scenesArray[currentScene].GetUserScene() != nullptr && "Starting scene was never created");

	scenesArray[currentScene].Start();
	GraphicsSceneManagerAttorney::SceneManagerControl::SetStartingScene(startingScene);
}

void SceneManager::privExecuteUpdateStep()
{
	scenesArray[currentScene].ExecuteUpdateStep();
}

void SceneManager::privRecycleCommand(ComponentRegistrationCommand* pCommand)
{
	commandPool.RecycleObject(pCommand);
}

void SceneManager::privSynchronizeCurrentScene()
{
	scenesArray[currentScene].Synchronize();
}

void SceneManager::privRegisterComponentInputOnPressed(KeyboardInputComponent* pComponent, const Input::Keyboard& key)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegisterInputKeyboardKeyOnPressed, pComponent);
	pTempCommand->attributeValue.index = key;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privRegisterComponentInputOnHeld(KeyboardInputComponent* pComponent, const Input::Keyboard& key)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegisterInputKeyboardKeyOnHeld, pComponent);
	pTempCommand->attributeValue.index = key;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privRegisterComponentInputOnReleased(KeyboardInputComponent* pComponent, const Input::Keyboard& key)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegisterInputKeyboardKeyOnReleased, pComponent);
	pTempCommand->attributeValue.index = key;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privRegisterComponentInputOnPressed(KeyboardInputComponent* pComponent, const InputActions& action)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegisterInputKeyboardActionOnPressed, pComponent);
	pTempCommand->attributeValue.index = action;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privRegisterComponentInputOnHeld(KeyboardInputComponent* pComponent, const InputActions& action)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegisterInputKeyboardActionOnHeld, pComponent);
	pTempCommand->attributeValue.index = action;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privRegisterComponentInputOnReleased(KeyboardInputComponent* pComponent, const InputActions& action)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegisterInputKeyboardActionOnReleased, pComponent);
	pTempCommand->attributeValue.index = action;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privDeregisterComponentInputOnPressedInput(KeyboardInputComponent* pComponent, const int& index)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregisterInputKeyboardKeyOnPressed, pComponent);
	pTempCommand->attributeValue.index = index;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privDeregisterComponentInputOnHeldInput(KeyboardInputComponent* pComponent, const int& index)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregisterInputKeyboardKeyOnHeld, pComponent);
	pTempCommand->attributeValue.index = index;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privDeregisterComponentInputOnReleasedInput(KeyboardInputComponent* pComponent, const int& index)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregisterInputKeyboardKeyOnReleased, pComponent);
	pTempCommand->attributeValue.index = index;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privDeregisterComponentInputOnPressedAction(KeyboardInputComponent* pComponent, const int& index)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregisterInputKeyboardActionOnPressed, pComponent);
	pTempCommand->attributeValue.index = index;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privDeregisterComponentInputOnHeldAction(KeyboardInputComponent* pComponent, const int& index)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregisterInputKeyboardActionOnHeld, pComponent);
	pTempCommand->attributeValue.index = index;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privDeregisterComponentInputOnReleasedAction(KeyboardInputComponent* pComponent, const int& index)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregisterInputKeyboardActionOnReleased, pComponent);
	pTempCommand->attributeValue.index = index;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privRegisterComponentInputOnPressed(MouseInputComponent* pComponent, const Input::Mouse& key)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegisterInputMouseKeyOnPressed, pComponent);
	pTempCommand->attributeValue.index = key;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privRegisterComponentInputOnHeld(MouseInputComponent* pComponent, const Input::Mouse& key)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegisterInputMouseKeyOnHeld, pComponent);
	pTempCommand->attributeValue.index = key;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privRegisterComponentInputOnReleased(MouseInputComponent* pComponent, const Input::Mouse& key)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegisterInputMouseKeyOnReleased, pComponent);
	pTempCommand->attributeValue.index = key;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privRegisterComponentInputOnPressed(MouseInputComponent* pComponent, const InputActions& action)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegisterInputMouseActionOnPressed, pComponent);
	pTempCommand->attributeValue.index = action;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privRegisterComponentInputOnHeld(MouseInputComponent* pComponent, const InputActions& action)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegisterInputMouseActionOnHeld, pComponent);
	pTempCommand->attributeValue.index = action;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privRegisterComponentInputOnReleased(MouseInputComponent* pComponent, const InputActions& action)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegisterInputMouseActionOnReleased, pComponent);
	pTempCommand->attributeValue.index = action;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privDeregisterComponentInputOnPressedInput(MouseInputComponent* pComponent, const int& index)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregisterInputMouseKeyOnPressed, pComponent);
	pTempCommand->attributeValue.index = index;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privDeregisterComponentInputOnHeldInput(MouseInputComponent* pComponent, const int& index)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregisterInputMouseKeyOnHeld, pComponent);
	pTempCommand->attributeValue.index = index;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privDeregisterComponentInputOnReleasedInput(MouseInputComponent* pComponent, const int& index)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregisterInputMouseKeyOnReleased, pComponent);
	pTempCommand->attributeValue.index = index;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privDeregisterComponentInputOnPressedAction(MouseInputComponent* pComponent, const int& index)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregisterInputMouseActionOnPressed, pComponent);
	pTempCommand->attributeValue.index = index;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privDeregisterComponentInputOnHeldAction(MouseInputComponent* pComponent, const int& index)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregisterInputMouseActionOnHeld, pComponent);
	pTempCommand->attributeValue.index = index;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privDeregisterComponentInputOnReleasedAction(MouseInputComponent* pComponent, const int& index)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregisterInputMouseActionOnReleased, pComponent);
	pTempCommand->attributeValue.index = index;

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

Scene* SceneManager::privGetScene(const SceneName& sceneName)
{
	return scenesArray[sceneName].GetUserScene();
}

EngineScene& SceneManager::privGetEngineScene(const SceneName & sceneName)
{
	return scenesArray[sceneName];
}

void SceneManager::privRegisterComponent(SceneComponent* pComponent, const SceneName& sceneName)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionRegisterSceneComponent, pComponent);

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::privDeregisterComponent(SceneComponent* pComponent, const SceneName& sceneName)
{
	pTempCommand = commandPool.GetPooledObject();
	pTempCommand->Initialize(&actionDeregisterSceneComponent, pComponent);

	InsertCurrentRegistrationCommandIntoScene(pComponent->GetRegisteredScene());
}

void SceneManager::InsertCurrentRegistrationCommandIntoScene(const SceneName& sceneName)
{
	assert(scenesArray[sceneName].GetUserScene() != nullptr && "Trying to submit a command to a scene that does not exist");
	scenesArray[sceneName].InsertCommand(pTempCommand);
}

SceneManager::~SceneManager()
{
	//If the user's current scene still exists
	if (scenesArray[currentScene].IsActive())
	{
		scenesArray[currentScene].Stop();
	}

	//Execute all existing commands to ensure everyone gets cleaned up.
	privProccessSceneCreationAndDeletionCommands();

	while (queueChangeScene.GetSize() > 0)
	{
		pTempSceneChangeCommand = queueChangeScene.Pop();
		poolChangeScene.RecycleObject(pTempSceneChangeCommand);
	}

	for (unsigned int i = 0u; i < NumberOfScenes; ++i)
	{
		if (scenesArray[i].GetUserScene() != nullptr)
		{
			scenesArray[i].ShutDown();
			scenesArray[i].DeleteUserScene();
			GraphicsSceneManagerAttorney::SceneManagerControl::SantitizeScene(static_cast<SceneName>(i));
		}
	}
}
