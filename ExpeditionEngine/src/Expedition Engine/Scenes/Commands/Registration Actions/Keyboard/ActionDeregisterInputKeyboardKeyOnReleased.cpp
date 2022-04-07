#include "ActionDeregisterInputKeyboardKeyOnReleased.h"

#include "../../../EngineScene.h"

void ActionDeregisterInputKeyboardKeyOnReleased::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetKeyboardInputManager().DeregisterComponentOnReleasedKey(pComponent.KeyboardInput, attribute.index);
}