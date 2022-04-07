#ifndef CONTROLSCHEMESWITCHER_H
#define CONTROLSCHEMESWITCHER_H

#include "../../Expedition Engine/Scene Components/Input/Keyboard/KeyboardInputComponent.h"

class ControlSchemeSwitcher : public KeyboardInputComponent
{
public:
	ControlSchemeSwitcher();
	~ControlSchemeSwitcher();

private:
	void OnKeyPressed() override;
	void OnKeyHeld() override;
	void OnKeyReleased() override;

	bool isCurrentStateWASD = true;

};

#endif // !CONTROLSCHEMESWITCHER_H