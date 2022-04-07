#include "ActionRegisterInputMouseActionOnPressed.h"

#include "../../../EngineScene.h"

void ActionRegisterInputMouseActionOnPressed::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetMouseInputManager().RegisterComponentOnPressedAction(pComponent.MouseInput, attribute.index);
}
