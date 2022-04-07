#pragma once

#include "../../Expedition Engine/Scene Components/Input/Keyboard/KeyboardInputComponent.h"
#include "Update_FlashLight.h"

class Input_FlashLight : public KeyboardInputComponent
{
public:
	Update_FlashLight updateLight;

	bool flashOn = false;
	int lightNum = 0;

private:
	void OnKeyPressed() override;
	void OnKeyReleased() override;
};
