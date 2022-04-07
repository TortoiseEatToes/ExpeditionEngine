#include "ActionRegisterInputMouseActionOnHeld.h"

#include "../../../EngineScene.h"

void ActionRegisterInputMouseActionOnHeld::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetMouseInputManager().RegisterComponentOnHeldAction(pComponent.MouseInput, attribute.index);
}
