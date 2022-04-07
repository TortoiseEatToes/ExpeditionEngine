#include "ActionDeregisterInputKeyboardActionOnHeld.h"

#include "../../../EngineScene.h"

void ActionDeregisterInputKeyboardActionOnHeld::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetKeyboardInputManager().DeregisterComponentOnHeldAction(pComponent.KeyboardInput, attribute.index);
}
