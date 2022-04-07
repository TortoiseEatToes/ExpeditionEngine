#include "ActionDeregisterInputKeyboardActionOnReleased.h"

#include "../../../EngineScene.h"

void ActionDeregisterInputKeyboardActionOnReleased::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetKeyboardInputManager().DeregisterComponentOnReleasedAction(pComponent.KeyboardInput, attribute.index);
}
