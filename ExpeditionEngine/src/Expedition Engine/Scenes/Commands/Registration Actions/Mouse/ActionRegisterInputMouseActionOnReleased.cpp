#include "ActionRegisterInputMouseActionOnReleased.h"

#include "../../../EngineScene.h"

void ActionRegisterInputMouseActionOnReleased::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetMouseInputManager().RegisterComponentOnReleasedAction(pComponent.MouseInput, attribute.index);
}
