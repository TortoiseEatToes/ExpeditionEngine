#include "ActionDeregisterInputKeyboardActionOnPressed.h"

#include "../../../EngineScene.h"

void ActionDeregisterInputKeyboardActionOnPressed::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetKeyboardInputManager().DeregisterComponentOnPressedAction(pComponent.KeyboardInput, attribute.index);
}
