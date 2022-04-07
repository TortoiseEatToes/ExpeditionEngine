#include "ActionRegisterInputMouseKeyOnReleased.h"

#include "../../../EngineScene.h"

void ActionRegisterInputMouseKeyOnReleased::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetMouseInputManager().RegisterComponentOnReleasedKey(pComponent.MouseInput, attribute.index);
}
