#include "ActionRegisterInputKeyboardKeyOnHeld.h"

#include "../../../EngineScene.h"

void ActionRegisterInputKeyboardKeyOnHeld::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetKeyboardInputManager().RegisterComponentOnHeldKey(pComponent.KeyboardInput, attribute.index);
}
