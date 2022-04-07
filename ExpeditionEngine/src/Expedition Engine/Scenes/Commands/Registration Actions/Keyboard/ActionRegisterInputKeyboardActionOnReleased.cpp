#include "ActionRegisterInputKeyboardActionOnReleased.h"

#include "../../../EngineScene.h"

void ActionRegisterInputKeyboardActionOnReleased::Execute(EngineScene& engineScene, Component& pComponent, Atribute& attribute)
{
	engineScene.GetKeyboardInputManager().RegisterComponentOnReleasedAction(pComponent.KeyboardInput, attribute.index);
}
