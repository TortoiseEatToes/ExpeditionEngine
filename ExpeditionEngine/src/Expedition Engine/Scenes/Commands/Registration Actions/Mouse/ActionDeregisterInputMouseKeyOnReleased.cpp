#include "ActionDeregisterInputMouseKeyOnReleased.h"

#include "../../../EngineScene.h"

void ActionDeregisterInputMouseKeyOnReleased::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetMouseInputManager().DeregisterComponentOnReleasedKey(pComponent.MouseInput, attribute.index);
}
