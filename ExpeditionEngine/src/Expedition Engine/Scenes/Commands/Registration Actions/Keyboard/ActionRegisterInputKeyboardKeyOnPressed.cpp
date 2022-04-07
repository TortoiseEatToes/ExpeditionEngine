#include "ActionRegisterInputKeyboardKeyOnPressed.h"

#include "../../../EngineScene.h"

void ActionRegisterInputKeyboardKeyOnPressed::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetKeyboardInputManager().RegisterComponentOnPressedKey(pComponent.KeyboardInput, attribute.index);
}