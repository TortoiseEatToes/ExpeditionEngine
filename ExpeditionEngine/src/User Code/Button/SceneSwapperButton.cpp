#include "SceneSwapperButton.h"

#include "../../Expedition Engine/Scenes/SceneManager.h"

SceneSwapperButton::SceneSwapperButton(SceneName sceneToExistIn, Image* spriteImage, Rect* rectangle)
	: Button(sceneToExistIn, spriteImage, rectangle)
{
}

void SceneSwapperButton::OnMouseClicked()
{
	SceneManager::ChangeScene(sceneToSwapTo);
}

void SceneSwapperButton::OnMouseHeld()
{

}

void SceneSwapperButton::OnMouseReleased()
{

}
