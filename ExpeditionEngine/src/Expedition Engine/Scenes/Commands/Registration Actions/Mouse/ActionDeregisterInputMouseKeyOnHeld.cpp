#include "ActionDeregisterInputMouseKeyOnHeld.h"

#include "../../../EngineScene.h"

void ActionDeregisterInputMouseKeyOnHeld::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetMouseInputManager().DeregisterComponentOnHeldKey(pComponent.MouseInput, attribute.index);
}
