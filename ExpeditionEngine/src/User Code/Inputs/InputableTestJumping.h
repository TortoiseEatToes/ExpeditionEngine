#ifndef InputComponentTESTJUMPING_H
#define InputComponentTESTJUMPING_H

#include "../../Expedition Engine/Game Object/GameObject.h"

#include <stdio.h>


class InputComponentTestJumping : public KeyboardInputComponent
{
public:

private:

	void OnKeyPressed() override
	{
		printf("Jump was pressed\n");
	}
	void OnKeyHeld() override
	{
		printf("Jump was held\n");
	}
	void OnKeyReleased() override
	{
		printf("Jump was released\n");
	}
};

#endif // !InputComponentTESTJUMPING_H
