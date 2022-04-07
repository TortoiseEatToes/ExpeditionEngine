#include "Footstep_Input.h"

Footstep_Input::Footstep_Input() : emitter(AudioClipName::AudioFootSteps, &callback)
{
}

Footstep_Input::~Footstep_Input()
{
}

void Footstep_Input::OnKeyPressed()
{
	if(keysPressed == 0)
		emitter.Play(1);

	keysPressed++;
}

void Footstep_Input::OnKeyReleased()
{
	keysPressed--;

	if(keysPressed == 0)
		emitter.Stop();
	//update.StopUpdating();
}
