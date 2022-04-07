//#pragma once
//
//#include "../../Expedition Engine/UI/UIElements/Button.h"
//
//class Rect;
//
//class SceneSwapperButton : public Button
//{
//public:
//	SceneSwapperButton() = delete;
//	SceneSwapperButton(SceneName sceneToExistIn, Image* spriteImage, Rect* rectangle);
//	SceneSwapperButton(const SceneSwapperButton& other) = delete;
//	SceneSwapperButton& operator= (const SceneSwapperButton& other) = delete;
//	~SceneSwapperButton() = default;
//
//	SceneName sceneToSwapTo;
//
//private:
//
//	void OnMouseClicked() override;
//	void OnMouseHeld() override;
//	void OnMouseReleased() override;
//};