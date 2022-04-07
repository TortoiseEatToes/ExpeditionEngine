#pragma once
#include "SceneManager.h"

#include "../Scene Components/Game Object/GameObject.h"

class SceneManagerAttorney
{
public:
	struct EngineControl
	{
	private:
		friend class ExpeditionEngine;
		static void Initialize()
		{
			SceneManager::Initialize();
		}

		static void StartFirstScene()
		{
			SceneManager::StartFirstScene();
		}

		static void Terminate()
		{
			SceneManager::Terminate();
		}
	};

	class EngineSceneGetter
	{
	private:
		friend class CollisionComponent;
		friend class Camera;

		static EngineScene& GetEngineScene(const SceneName& sceneName)
		{
			return SceneManager::GetEngineScene(sceneName);
		}
	};

	struct UpdateFrameControl
	{
	private:
		friend class Task_UpdateFrame;
		static void ExecuteUpdateStep()
		{
			SceneManager::ExecuteUpdateStep();
		}
	};

	class SynchronizeSceneControl
	{
	private:
		friend class Task_SynchronizeCurrentScene;

		static void SynchronizeCurrentScene()
		{
			SceneManager::SynchronizeCurrentScene();
		}
	};
	
	struct SceneComponentControl
	{
	private:
		friend class SceneComponent;

		static void RegisterComponent(SceneComponent* pComponent, const SceneName& sceneName)
		{
			SceneManager::RegisterComponent(pComponent, sceneName);
		}

		static void DeregisterComponent(SceneComponent* pComponent, const SceneName& sceneName)
		{
			SceneManager::DeregisterComponent(pComponent, sceneName);
		}
	};

	class ResolveFrameControl
	{
	private:
		friend class Task_ResolveFrame;

		static void ProccessSceneCreationAndDeletionCommands()
		{
			SceneManager::ProccessSceneCreationAndDeletionCommands();
		}
	};

	class PostFrameEndControl
	{
	private:
		friend class Task_PostFrameEnd;

		static void ProcessSceneChangeCommands()
		{
			SceneManager::ProcessSceneChangeCommands();
		}
	};

	class CommandControl
	{
	private:
		//Scene Commands
		friend class ComponentRegistrationCommand;

		static void RecycleCommand(ComponentRegistrationCommand* pCommand)
		{
			SceneManager::RecycleCommand(pCommand);
		}
	};

	class ManagerCommandControl
	{
	private:
		friend class SceneDeletionCommand;
		friend class SceneChangeCommand;

		static void DestroyScene(const SceneName& sceneName)
		{
			SceneManager::cmdDestroyScene(sceneName);
		}

		static void ChangeScene(const SceneName& sceneName)
		{
			SceneManager::cmdChangeScene(sceneName);
		}
	};

	class GraphicsControl
	{
	private:
		friend class GraphicsScene;
		friend class GO_Data_Manager;

		static const CameraData& GetCurrentPerspectiveCameraData()
		{
			return SceneManager::GetCurrentPerspectiveCameraData();
		}

		static const CameraData& GetCurrentOrthographicCameraData()
		{
			return SceneManager::GetCurrentOrthographicCameraData();
		}
	};

	struct KeyboardInputControl
	{
	private:
		friend class KeyboardInputComponent;

		//Register Key
		static void RegisterComponentInputOnPressed(KeyboardInputComponent* pComponent, const Input::Keyboard& key)
		{
			SceneManager::RegisterComponentInputOnPressed(pComponent, key);
		}

		static void RegisterComponentInputOnHeld(KeyboardInputComponent* pComponent, const Input::Keyboard& key)
		{
			SceneManager::RegisterComponentInputOnHeld(pComponent, key);
		}

		static void RegisterComponentInputOnReleased(KeyboardInputComponent* pComponent, const Input::Keyboard& key)
		{
			SceneManager::RegisterComponentInputOnReleased(pComponent, key);
		}

		//Register Action
		static void RegisterComponentInputOnPressed(KeyboardInputComponent* pComponent, const InputActions& action)
		{
			SceneManager::RegisterComponentInputOnPressed(pComponent, action);
		}

		static void RegisterComponentInputOnHeld(KeyboardInputComponent* pComponent, const InputActions& action)
		{
			SceneManager::RegisterComponentInputOnHeld(pComponent, action);
		}

		static void RegisterComponentInputOnReleased(KeyboardInputComponent* pComponent, const InputActions& action)
		{
			SceneManager::RegisterComponentInputOnReleased(pComponent, action);
		}

		//Deregister Input
		static void DeregisterComponentInputOnPressedInput(KeyboardInputComponent* pComponent, const int& index)
		{
			SceneManager::DeregisterComponentInputOnPressedInput(pComponent, index);
		}

		static void DeregisterComponentInputOnHeldInput(KeyboardInputComponent* pComponent, const int& index)
		{
			SceneManager::DeregisterComponentInputOnHeldInput(pComponent, index);
		}

		static void DeregisterComponentInputOnReleasedInput(KeyboardInputComponent* pComponent, const int& index)
		{
			SceneManager::DeregisterComponentInputOnReleasedInput(pComponent, index);
		}

		//Deregister Action
		static void DeregisterComponentInputOnPressedAction(KeyboardInputComponent* pComponent, const int& index)
		{
			SceneManager::DeregisterComponentInputOnPressedAction(pComponent,index);
		}

		static void DeregisterComponentInputOnHeldAction(KeyboardInputComponent* pComponent, const int& index)
		{
			SceneManager::DeregisterComponentInputOnHeldAction(pComponent, index);
		}

		static void DeregisterComponentInputOnReleasedAction(KeyboardInputComponent* pComponent, const int& index)
		{
			SceneManager::DeregisterComponentInputOnReleasedAction(pComponent, index);
		}
	};

	struct MouseInputControl
	{
	private:
		friend class MouseInputComponent;

		//Register Key
		static void RegisterComponentInputOnPressed(MouseInputComponent* pComponent, const Input::Mouse& key)
		{
			SceneManager::RegisterComponentInputOnPressed(pComponent, key);
		}

		static void RegisterComponentInputOnHeld(MouseInputComponent* pComponent, const Input::Mouse& key)
		{
			SceneManager::RegisterComponentInputOnHeld(pComponent, key);
		}

		static void RegisterComponentInputOnReleased(MouseInputComponent* pComponent, const Input::Mouse& key)
		{
			SceneManager::RegisterComponentInputOnReleased(pComponent, key);
		}

		//Register Action
		static void RegisterComponentInputOnPressed(MouseInputComponent* pComponent, const InputActions& action)
		{
			SceneManager::RegisterComponentInputOnPressed(pComponent, action);
		}

		static void RegisterComponentInputOnHeld(MouseInputComponent* pComponent, const InputActions& action)
		{
			SceneManager::RegisterComponentInputOnHeld(pComponent, action);
		}

		static void RegisterComponentInputOnReleased(MouseInputComponent* pComponent, const InputActions& action)
		{
			SceneManager::RegisterComponentInputOnReleased(pComponent, action);
		}

		//Deregister Input
		static void DeregisterComponentInputOnPressedInput(MouseInputComponent* pComponent, const int& index)
		{
			SceneManager::DeregisterComponentInputOnPressedInput(pComponent, index);
		}

		static void DeregisterComponentInputOnHeldInput(MouseInputComponent* pComponent, const int& index)
		{
			SceneManager::DeregisterComponentInputOnHeldInput(pComponent, index);
		}

		static void DeregisterComponentInputOnReleasedInput(MouseInputComponent* pComponent, const int& index)
		{
			SceneManager::DeregisterComponentInputOnReleasedInput(pComponent, index);
		}

		//Deregister Actions
		static void DeregisterComponentInputOnPressedAction(MouseInputComponent* pComponent, const int& index)
		{
			SceneManager::DeregisterComponentInputOnPressedAction(pComponent, index);
		}

		static void DeregisterComponentInputOnHeldAction(MouseInputComponent* pComponent, const int& index)
		{
			SceneManager::DeregisterComponentInputOnHeldAction(pComponent, index);
		}

		static void DeregisterComponentInputOnReleasedAction(MouseInputComponent* pComponent, const int& index)
		{
			SceneManager::DeregisterComponentInputOnReleasedAction(pComponent, index);
		}
	};
};