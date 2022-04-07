#pragma once

#include "../../Expedition Engine/Scene Components/Input/Keyboard/KeyboardInputComponent.h"

class Input_CameraFwdBack : public KeyboardInputComponent
{
public:

	float speed;

private:
	void OnKeyHeld() override;

};