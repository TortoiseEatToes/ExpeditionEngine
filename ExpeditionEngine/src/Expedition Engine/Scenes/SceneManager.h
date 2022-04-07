#pragma once

#include "SceneAttorney.h"

#include "../../Expedition Resources/SceneSettings.h"

#include "../Containers/Pool.h"

#include "Commands/SceneCommandIncludes.h"

#include "../GraphicsScene/GraphicsSceneManagerAttorney.h"

#include "Commands/Manager Commands/SceneChangeCommand.h"
#include "Commands/Manager Commands/SceneCreationCommand.h"
#include "Commands/Manager Commands/SceneDeletionCommand.h"

#include "EngineScene.h"

class Camera;
class CameraData;


class SceneManager
{
public:

	/// <summary>Get a pointer to the current scene.</summary>
	/// <returns>The current scene</returns>
	static Scene* GetCurrentScene()
	{
		return Instance().privGetCurrentScene();
	}

	/// <summary>Get the current perspective camera.</summary>
	/// <returns>The current perspective camera</returns>
	static Camera* const GetCurrentPerspectiveCamera()
	{
		return GetCurrentScene()->GetCurrentPerspectiveCamera();
	}

	/// <summary>Get the current orthographic camera.</summary>
	/// <returns>The current orthographic camera</returns>
	static Camera*const GetCurrentOrthographicCamera()
	{
		return GetCurrentScene()->GetCurrentOrthographicCamera();
	}

	/// <summary>Use this to create a scene of your given class with the given name.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this scene should be named</param>
	template<typename T>
	static void CreateScene(SceneName nameOfSceneToCreate)
	{
		Instance().privCreateScene<T>(nameOfSceneToCreate);
	}
	
	/// <summary>Use this to destroy an old scene that you no longer need.  You can reuse the name with another scene after this space has been cleared.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that should be destroyed</param>
	static void DestroyScene(SceneName nameOfSceneToDestroy)
	{
		Instance().privDestroyScene(nameOfSceneToDestroy);
	}
	
	/// <summary>Change the current scene to a new scene.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that should become the new current scene</param>
	static void ChangeScene(SceneName nextSceneName)
	{
		Instance().privChangeScene(nextSceneName);
	}

	/// <summary>Use this to get a scene.  Note, if you have not created a scene with that name, this will return a nullptr.</summary>
	/// <param name="sceneToRegisterInto">The SceneName to get</param>
	/// <returns>Return a pointer to scene with that name</returns> 
	static Scene* GetScene(SceneName sceneName)
	{
		return Instance().privGetScene(sceneName);
	}

	/// <summary>Get the perspective camera from a specific scene.</summary>
	/// <returns>The current perspective camera</returns>
	static Camera* const GetCurrentPerspectiveCamera(SceneName sceneName)
	{
		return GetScene(sceneName)->GetCurrentPerspectiveCamera();
	}

	/// <summary>Get the orthographic camera from a specific scene.</summary>
	/// <returns>The current orthographic camera</returns>
	static Camera*const GetCurrentOrthographicCamera(SceneName sceneName)
	{
		return GetScene(sceneName)->GetCurrentOrthographicCamera();
	}

private:
	friend class SceneManagerAttorney;

	SceneManager();
	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator= (const SceneManager& other) = delete;
	~SceneManager();

	static void Initialize()
	{
		pInstance = new SceneManager();
	}
	static void Terminate()
	{
		delete pInstance;
	}

	static SceneManager& Instance()
	{
		return *pInstance;
	}

	static void StartFirstScene()
	{
		Instance().privStartFirstScene();
	}
	void privStartFirstScene();

	//HACK!!!   I did this to avoid creating an include loop between the Manager, Attorney, and command
	//From what I can tell, you cannot create function declerations in .cpp files, which makes include loops happen
	template<typename T>
	friend class SceneCreationCommand;

	static void ExecuteUpdateStep()
	{
		Instance().privExecuteUpdateStep();
	}
	void privExecuteUpdateStep();

	template<typename T>
	void privCreateScene(const SceneName& nameOfSceneToCreate)
	{
		pTempManagerCommand = new SceneCreationCommand<T>();
		pTempManagerCommand->Initialize(nameOfSceneToCreate);
		queueCreateScene.Push(pTempManagerCommand);
	}

	template<typename T>
	static void cmdCreateScene(const SceneName& nameOfSceneToCreate)
	{
		Instance().cmdprivCreateScene<T>(nameOfSceneToCreate);
	}

	template<typename T>
	void cmdprivCreateScene(const SceneName& nameOfSceneToCreate)
	{
		assert(scenesArray[nameOfSceneToCreate].GetUserScene() == nullptr && "Trying to create a scene that already exists");

		GraphicsSceneManagerAttorney::SceneManagerControl::InitializeScene(nameOfSceneToCreate);
		scenesArray[nameOfSceneToCreate].SetUserScene(new T());
		scenesArray[nameOfSceneToCreate].Initialize();
	}

	Scene* privGetCurrentScene();

	static void ProccessSceneCreationAndDeletionCommands()
	{
		Instance().privProccessSceneCreationAndDeletionCommands();
	}
	void privProccessSceneCreationAndDeletionCommands();

	static void ProcessSceneChangeCommands()
	{
		Instance().privProcessSceneChangeCommands();
	}
	void privProcessSceneChangeCommands();

	void privDestroyScene(const SceneName& sceneName);
	static void cmdDestroyScene(const SceneName& sceneName)
	{
		Instance().cmdprivDestroyScene(sceneName);
	}
	void cmdprivDestroyScene(const SceneName& sceneName);

	void privChangeScene(const SceneName& sceneName);
	static void cmdChangeScene(const SceneName& sceneName)
	{
		Instance().cmdprivChangeScene(sceneName);
	}
	void cmdprivChangeScene(const SceneName& sceneName);

	static const CameraData& GetCurrentPerspectiveCameraData()
	{
		return Instance().privGetCurrentPerspectiveCameraData();
	}
	const CameraData& privGetCurrentPerspectiveCameraData() const;

	static const CameraData& GetCurrentOrthographicCameraData()
	{
		return Instance().privGetCurrentOrthographicCameraData();
	}
	const CameraData& privGetCurrentOrthographicCameraData() const;

	static void RecycleCommand(ComponentRegistrationCommand* pCommand)
	{
		Instance().privRecycleCommand(pCommand);
	}
	void privRecycleCommand(ComponentRegistrationCommand* pCommand);


	static void SynchronizeCurrentScene()
	{
		Instance().privSynchronizeCurrentScene();
	}
	void privSynchronizeCurrentScene();

	//Keyboard
	static void RegisterComponentInputOnPressed(KeyboardInputComponent* pComponent, const Input::Keyboard& key)
	{
		Instance().privRegisterComponentInputOnPressed(pComponent, key);
	}
	void privRegisterComponentInputOnPressed(KeyboardInputComponent* pComponent, const Input::Keyboard& key);

	static void RegisterComponentInputOnHeld(KeyboardInputComponent* pComponent, const Input::Keyboard& key)
	{
		Instance().privRegisterComponentInputOnHeld(pComponent, key);
	}
	void privRegisterComponentInputOnHeld(KeyboardInputComponent* pComponent, const Input::Keyboard& key);

	static void RegisterComponentInputOnReleased(KeyboardInputComponent* pComponent, const Input::Keyboard& key)
	{
		Instance().privRegisterComponentInputOnReleased(pComponent, key);
	}
	void privRegisterComponentInputOnReleased(KeyboardInputComponent* pComponent, const Input::Keyboard& key);

	//Register Action
	static void RegisterComponentInputOnPressed(KeyboardInputComponent* pComponent, const InputActions& action)
	{
		Instance().privRegisterComponentInputOnPressed(pComponent, action);
	}
	void privRegisterComponentInputOnPressed(KeyboardInputComponent* pComponent, const InputActions& action);

	static void RegisterComponentInputOnHeld(KeyboardInputComponent* pComponent, const InputActions& action)
	{
		Instance().privRegisterComponentInputOnHeld(pComponent, action);
	}
	void privRegisterComponentInputOnHeld(KeyboardInputComponent* pComponent, const InputActions& action);

	static void RegisterComponentInputOnReleased(KeyboardInputComponent* pComponent, const InputActions& action)
	{
		Instance().privRegisterComponentInputOnReleased(pComponent, action);
	}
	void privRegisterComponentInputOnReleased(KeyboardInputComponent* pComponent, const InputActions& action);

	//Deregister Input
	static void DeregisterComponentInputOnPressedInput(KeyboardInputComponent* pComponent, const int& index)
	{
		Instance().privDeregisterComponentInputOnPressedInput(pComponent, index);
	}
	void privDeregisterComponentInputOnPressedInput(KeyboardInputComponent* pComponent, const int& index);

	static void DeregisterComponentInputOnHeldInput(KeyboardInputComponent* pComponent, const int& index)
	{
		Instance().privDeregisterComponentInputOnHeldInput(pComponent, index);
	}
	void privDeregisterComponentInputOnHeldInput(KeyboardInputComponent* pComponent, const int& index);

	static void DeregisterComponentInputOnReleasedInput(KeyboardInputComponent* pComponent, const int& index)
	{
		Instance().privDeregisterComponentInputOnReleasedInput(pComponent, index);
	}
	void privDeregisterComponentInputOnReleasedInput(KeyboardInputComponent* pComponent, const int& index);

	//Deregister Action
	static void DeregisterComponentInputOnPressedAction(KeyboardInputComponent* pComponent, const int& index)
	{
		Instance().privDeregisterComponentInputOnPressedAction(pComponent, index);
	}
	void privDeregisterComponentInputOnPressedAction(KeyboardInputComponent* pComponent, const int& index);

	static void DeregisterComponentInputOnHeldAction(KeyboardInputComponent* pComponent, const int& index)
	{
		Instance().privDeregisterComponentInputOnHeldAction(pComponent, index);
	}
	void privDeregisterComponentInputOnHeldAction(KeyboardInputComponent* pComponent, const int& index);

	static void DeregisterComponentInputOnReleasedAction(KeyboardInputComponent* pComponent, const int& index)
	{
		Instance().privDeregisterComponentInputOnReleasedAction(pComponent, index);
	}
	void privDeregisterComponentInputOnReleasedAction(KeyboardInputComponent* pComponent, const int& index);

	//Mouse
	//Register Key
	static void RegisterComponentInputOnPressed(MouseInputComponent* pComponent, const Input::Mouse& key)
	{
		Instance().privRegisterComponentInputOnPressed(pComponent, key);
	}
	void privRegisterComponentInputOnPressed(MouseInputComponent* pComponent, const Input::Mouse& key);

	static void RegisterComponentInputOnHeld(MouseInputComponent* pComponent, const Input::Mouse& key)
	{
		Instance().privRegisterComponentInputOnHeld(pComponent, key);
	}
	void privRegisterComponentInputOnHeld(MouseInputComponent* pComponent, const Input::Mouse& key);

	static void RegisterComponentInputOnReleased(MouseInputComponent* pComponent, const Input::Mouse& key)
	{
		Instance().privRegisterComponentInputOnReleased(pComponent, key);
	}
	void privRegisterComponentInputOnReleased(MouseInputComponent* pComponent, const Input::Mouse& key);

	//Register Action
	static void RegisterComponentInputOnPressed(MouseInputComponent* pComponent, const InputActions& action)
	{
		Instance().privRegisterComponentInputOnPressed(pComponent, action);
	}
	void privRegisterComponentInputOnPressed(MouseInputComponent* pComponent, const InputActions& action);

	static void RegisterComponentInputOnHeld(MouseInputComponent* pComponent, const InputActions& action)
	{
		Instance().privRegisterComponentInputOnHeld(pComponent, action);
	}
	void privRegisterComponentInputOnHeld(MouseInputComponent* pComponent, const InputActions& action);

	static void RegisterComponentInputOnReleased(MouseInputComponent* pComponent, const InputActions& action)
	{
		Instance().privRegisterComponentInputOnReleased(pComponent, action);
	}
	void privRegisterComponentInputOnReleased(MouseInputComponent* pComponent, const InputActions& action);

	//Deregister Input
	static void DeregisterComponentInputOnPressedInput(MouseInputComponent* pComponent, const int& index)
	{
		Instance().privDeregisterComponentInputOnPressedInput(pComponent, index);
	}
	void privDeregisterComponentInputOnPressedInput(MouseInputComponent* pComponent, const int& index);

	static void DeregisterComponentInputOnHeldInput(MouseInputComponent* pComponent, const int& index)
	{
		Instance().privDeregisterComponentInputOnHeldInput(pComponent, index);
	}
	void privDeregisterComponentInputOnHeldInput(MouseInputComponent* pComponent, const int& index);

	static void DeregisterComponentInputOnReleasedInput(MouseInputComponent* pComponent, const int& index)
	{
		Instance().privDeregisterComponentInputOnReleasedInput(pComponent, index);
	}
	void privDeregisterComponentInputOnReleasedInput(MouseInputComponent* pComponent, const int& index);

	//Deregister Actions
	static void DeregisterComponentInputOnPressedAction(MouseInputComponent* pComponent, const int& index)
	{
		Instance().privDeregisterComponentInputOnPressedAction(pComponent, index);
	}
	void privDeregisterComponentInputOnPressedAction(MouseInputComponent* pComponent, const int& index);

	static void DeregisterComponentInputOnHeldAction(MouseInputComponent* pComponent, const int& index)
	{
		Instance().privDeregisterComponentInputOnHeldAction(pComponent, index);
	}
	void privDeregisterComponentInputOnHeldAction(MouseInputComponent* pComponent, const int& index);

	static void DeregisterComponentInputOnReleasedAction(MouseInputComponent* pComponent, const int& index)
	{
		Instance().privDeregisterComponentInputOnReleasedAction(pComponent, index);
	}
	void privDeregisterComponentInputOnReleasedAction(MouseInputComponent* pComponent, const int& index);

	Scene* privGetScene(const SceneName& sceneName);

	static EngineScene& GetEngineScene(const SceneName& sceneName)
	{
		return Instance().privGetEngineScene(sceneName);
	}
	EngineScene& privGetEngineScene(const SceneName& sceneName);

	static void RegisterComponent(SceneComponent* pComponent, const SceneName& sceneName)
	{
		Instance().privRegisterComponent(pComponent, sceneName);
	}
	void privRegisterComponent(SceneComponent* pComponent, const SceneName& sceneName);

	static void DeregisterComponent(SceneComponent* pComponent, const SceneName& sceneName)
	{
		Instance().privDeregisterComponent(pComponent, sceneName);
	}
	void privDeregisterComponent(SceneComponent* pComponent, const SceneName& sceneName);

	//Scene Registration command
	Pool<ComponentRegistrationCommand> commandPool;
	Pool<SceneChangeCommand> poolChangeScene;
	Pool<SceneDeletionCommand> poolDestroyScene;

	Queue<SceneChangeCommand*> queueChangeScene;
	Queue<SceneDeletionCommand*> queueDestroyScene;
	Queue<SceneManagerCommand*> queueCreateScene;

	EngineScene scenesArray[NumberOfScenes];
	SceneName currentScene;

	static SceneManager* pInstance;

	SceneManagerCommand* pTempManagerCommand;
	SceneChangeCommand* pTempSceneChangeCommand;
	SceneDeletionCommand* pTempSceneDeletionCommand;
	ComponentRegistrationCommand* pTempCommand;

	void InsertCurrentRegistrationCommandIntoScene(const SceneName& sceneName);


	//--------------------------- Actions -----------------------------------
	//Mouse
	ActionDeregisterInputMouseActionOnHeld actionDeregisterInputMouseActionOnHeld;
	ActionDeregisterInputMouseActionOnPressed actionDeregisterInputMouseActionOnPressed;
	ActionDeregisterInputMouseActionOnReleased actionDeregisterInputMouseActionOnReleased;

	ActionDeregisterInputMouseKeyOnHeld actionDeregisterInputMouseKeyOnHeld;
	ActionDeregisterInputMouseKeyOnPressed actionDeregisterInputMouseKeyOnPressed;
	ActionDeregisterInputMouseKeyOnReleased actionDeregisterInputMouseKeyOnReleased;

	ActionRegisterInputMouseActionOnHeld actionRegisterInputMouseActionOnHeld;
	ActionRegisterInputMouseActionOnPressed actionRegisterInputMouseActionOnPressed;
	ActionRegisterInputMouseActionOnReleased actionRegisterInputMouseActionOnReleased;

	ActionRegisterInputMouseKeyOnHeld actionRegisterInputMouseKeyOnHeld;
	ActionRegisterInputMouseKeyOnPressed actionRegisterInputMouseKeyOnPressed;
	ActionRegisterInputMouseKeyOnReleased actionRegisterInputMouseKeyOnReleased;

	//Keyboard
	ActionDeregisterInputKeyboardActionOnHeld actionDeregisterInputKeyboardActionOnHeld;
	ActionDeregisterInputKeyboardActionOnPressed actionDeregisterInputKeyboardActionOnPressed;
	ActionDeregisterInputKeyboardActionOnReleased actionDeregisterInputKeyboardActionOnReleased;

	ActionDeregisterInputKeyboardKeyOnHeld actionDeregisterInputKeyboardKeyOnHeld;
	ActionDeregisterInputKeyboardKeyOnPressed actionDeregisterInputKeyboardKeyOnPressed;
	ActionDeregisterInputKeyboardKeyOnReleased actionDeregisterInputKeyboardKeyOnReleased;

	ActionRegisterInputKeyboardActionOnHeld actionRegisterInputKeyboardActionOnHeld;
	ActionRegisterInputKeyboardActionOnPressed actionRegisterInputKeyboardActionOnPressed;
	ActionRegisterInputKeyboardActionOnReleased actionRegisterInputKeyboardActionOnReleased;

	ActionRegisterInputKeyboardKeyOnHeld actionRegisterInputKeyboardKeyOnHeld;
	ActionRegisterInputKeyboardKeyOnPressed actionRegisterInputKeyboardKeyOnPressed;
	ActionRegisterInputKeyboardKeyOnReleased actionRegisterInputKeyboardKeyOnReleased;

	//Scene Component
	ActionDeregisterSceneComponent actionDeregisterSceneComponent;
	ActionRegisterSceneComponent actionRegisterSceneComponent;
	//---------------------------------------------------------------------------------------
};