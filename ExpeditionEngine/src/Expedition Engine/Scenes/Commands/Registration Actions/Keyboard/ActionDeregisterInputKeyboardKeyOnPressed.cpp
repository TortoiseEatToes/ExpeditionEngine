#include "ActionDeregisterInputKeyboardKeyOnPressed.h"

#include "../../../EngineScene.h"

void ActionDeregisterInputKeyboardKeyOnPressed::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetKeyboardInputManager().DeregisterComponentOnPressedKey(pComponent.KeyboardInput, attribute.index);
}
