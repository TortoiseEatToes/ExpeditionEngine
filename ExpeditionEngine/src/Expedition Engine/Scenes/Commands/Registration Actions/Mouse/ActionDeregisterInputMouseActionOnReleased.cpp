#include "ActionDeregisterInputMouseActionOnReleased.h"

#include "../../../EngineScene.h"

void ActionDeregisterInputMouseActionOnReleased::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetMouseInputManager().DeregisterComponentOnReleasedAction(pComponent.MouseInput, attribute.index);
}
