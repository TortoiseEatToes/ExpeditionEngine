#ifndef PLAYERCONTROLLERQUITGAME_H
#define PLAYERCONTROLLERQUITGAME_H

#include "../../Expedition Engine/Scene Components/Input/Keyboard/KeyboardInputComponent.h"

class PlayerControllerQuitGame : public KeyboardInputComponent
{
public:
	PlayerControllerQuitGame();
	~PlayerControllerQuitGame();

private:
	void OnKeyPressed() override;
	void OnKeyHeld() override;
	void OnKeyReleased() override;

};

#endif // !PLAYERCONTROLLERQUITGAME_H