#include "ActionDeregisterInputMouseKeyOnPressed.h"

#include "../../../EngineScene.h"

void ActionDeregisterInputMouseKeyOnPressed::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetMouseInputManager().DeregisterComponentOnPressedKey(pComponent.MouseInput, attribute.index);
}
