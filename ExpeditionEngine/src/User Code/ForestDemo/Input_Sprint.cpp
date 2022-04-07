#include "Input_Sprint.h"
#include "Forest_Camera.h"

void Input_Sprint::OnKeyPressed()
{
	cam->SetSpeed(sprintSpeed);
}

void Input_Sprint::OnKeyReleased()
{
	cam->SetSpeed(walkSpeed);
}
