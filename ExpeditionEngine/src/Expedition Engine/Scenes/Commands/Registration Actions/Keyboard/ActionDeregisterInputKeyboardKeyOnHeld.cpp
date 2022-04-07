#include "ActionDeregisterInputKeyboardKeyOnHeld.h"

#include "../../../EngineScene.h"

void ActionDeregisterInputKeyboardKeyOnHeld::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetKeyboardInputManager().DeregisterComponentOnHeldKey(pComponent.KeyboardInput, attribute.index);
}
