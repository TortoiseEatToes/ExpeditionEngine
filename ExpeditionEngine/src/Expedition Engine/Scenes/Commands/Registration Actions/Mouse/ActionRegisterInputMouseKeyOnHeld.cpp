#include "ActionRegisterInputMouseKeyOnHeld.h"

#include "../../../EngineScene.h"

void ActionRegisterInputMouseKeyOnHeld::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetMouseInputManager().RegisterComponentOnHeldKey(pComponent.MouseInput, attribute.index);
}
