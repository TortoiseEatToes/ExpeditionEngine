#ifndef ACTIONS_H
#define ACTIONS_H

//Define the InputActions that you want the input components to be able to register for.  
//This allows you to have all of your input components register for a generic action like "jump", but then rebind what physical input key or button actually triggers that InputEvent at runtime.
enum InputActions
{
	MoveForward,
	MoveBackward,
	MoveLeft,
	MoveRight,
	SwapScene,
	PlayerMove
};

static const unsigned int NumberOfActions = 6u;

#endif // !ACTIONS_H
