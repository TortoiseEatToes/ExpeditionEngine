#ifndef SceneSwapper_H
#define SceneSwapper_H

#include "../../Expedition Engine/Scene Components/Input/Keyboard/KeyboardInputComponent.h"
#include "../../Expedition Resources/SceneSettings.h"

class SceneSwapper : public KeyboardInputComponent
{
public:
	SceneSwapper() = default;
	~SceneSwapper() = default;

	SceneName sceneToSwapTo;

private:
	void OnKeyPressed() override;
	void OnKeyHeld() override;
	void OnKeyReleased() override;
};

#endif // !SceneSwapper_H