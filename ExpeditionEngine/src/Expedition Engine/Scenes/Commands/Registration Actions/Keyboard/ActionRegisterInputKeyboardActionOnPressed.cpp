#include "ActionRegisterInputKeyboardActionOnPressed.h"

#include "../../../EngineScene.h"

void ActionRegisterInputKeyboardActionOnPressed::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetKeyboardInputManager().RegisterComponentOnPressedAction(pComponent.KeyboardInput, attribute.index);
}
