#include "ActionRegisterInputMouseKeyOnPressed.h"

#include "../../../EngineScene.h"

void ActionRegisterInputMouseKeyOnPressed::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetMouseInputManager().RegisterComponentOnPressedKey(pComponent.MouseInput, attribute.index);
}
