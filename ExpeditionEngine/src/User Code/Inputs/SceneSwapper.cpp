#include "SceneSwapper.h"
#include "../../Expedition Engine/Scenes/SceneManager.h"

void SceneSwapper::OnKeyPressed()
{
	SceneManager::ChangeScene(sceneToSwapTo);
}

void SceneSwapper::OnKeyHeld()
{
}

void SceneSwapper::OnKeyReleased()
{
}
