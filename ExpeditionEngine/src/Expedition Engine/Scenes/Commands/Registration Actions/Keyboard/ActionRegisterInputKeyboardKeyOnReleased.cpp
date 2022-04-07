#include "ActionRegisterInputKeyboardKeyOnReleased.h"

#include "../../../EngineScene.h"

void ActionRegisterInputKeyboardKeyOnReleased::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetKeyboardInputManager().RegisterComponentOnReleasedKey(pComponent.KeyboardInput, attribute.index);
}