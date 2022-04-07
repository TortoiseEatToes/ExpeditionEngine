#include "ActionDeregisterInputMouseActionOnPressed.h"

#include "../../../EngineScene.h"

void ActionDeregisterInputMouseActionOnPressed::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetMouseInputManager().DeregisterComponentOnPressedAction(pComponent.MouseInput, attribute.index);
}
