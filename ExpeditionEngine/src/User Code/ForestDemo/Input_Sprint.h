#pragma once

#include "../../Expedition Engine/Scene Components/Input/Keyboard/KeyboardInputComponent.h"

class Forest_Camera;

class Input_Sprint : public KeyboardInputComponent
{
public:
	Forest_Camera* cam;

	float sprintSpeed;
	float walkSpeed;

private:
	void OnKeyPressed() override;
	void OnKeyReleased() override;
};