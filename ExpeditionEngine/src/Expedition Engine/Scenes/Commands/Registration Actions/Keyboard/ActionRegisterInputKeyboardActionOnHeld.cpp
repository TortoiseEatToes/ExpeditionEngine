#include "ActionRegisterInputKeyboardActionOnHeld.h"

#include "../../../EngineScene.h"

void ActionRegisterInputKeyboardActionOnHeld::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetKeyboardInputManager().RegisterComponentOnHeldAction(pComponent.KeyboardInput, attribute.index);
}
