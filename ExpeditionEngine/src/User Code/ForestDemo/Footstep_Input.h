#pragma once

#include "../../Expedition Engine/Scene Components/Input/Keyboard/KeyboardInputComponent.h"
#include "../../Expedition Engine/Scene Components/Audio Emitter/AudioEmitter.h"
#include "Footstep_Callback.h"


class Footstep_Input : public KeyboardInputComponent
{
public:
	Footstep_Input();
	~Footstep_Input();

	Footstep_Input(Footstep_Input&&) = delete;
	Footstep_Input(const Footstep_Input&) = delete;
	const Footstep_Input operator = (Footstep_Input&&) = delete;
	const Footstep_Input operator = (const Footstep_Input&) = delete;

	AudioEmitter emitter;
	Footstep_Callback callback;

private:
	void OnKeyPressed() override;
	void OnKeyReleased() override;

	int keysPressed = 0;
};
