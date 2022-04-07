#include "ActionDeregisterInputMouseActionOnHeld.h"

#include "../../../EngineScene.h"

void ActionDeregisterInputMouseActionOnHeld::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetMouseInputManager().DeregisterComponentOnHeldAction(pComponent.MouseInput, attribute.index);
}
