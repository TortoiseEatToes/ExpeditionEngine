#include "MouseInputManager.h"

#include "../MouseInputComponent.h"

#include "../../Manager/ActionBindingSetting.h"

#include <Windows.h>

MouseInputManager::MouseInputManager()
{
	Initialize(userInputKeys[Input::LeftButton], 0x01);
	Initialize(userInputKeys[Input::RightButton], 0x02);
	Initialize(userInputKeys[Input::MiddleButton], 0x04);
	Initialize(userInputKeys[Input::X1Button], 0x05);
	Initialize(userInputKeys[Input::X2Button], 0x06);
}

MouseInputManager::~MouseInputManager()
{

}

void MouseInputManager::ProcessMouseInput()
{
	inputKeysToTrack.SetFront(iterator);
	while (!iterator.IsOutOfNodes())
	{
		iterator.GetCurrentObject()->UpdateState(GetKeyState(iterator.GetCurrentObject()->GetCode()) & 0x80);
		++iterator;
	}
}

void MouseInputManager::RegisterComponentOnPressedKey(MouseInputComponent* pMouseInputComponent, const int& keyIndex)
{
	userInputKeys[keyIndex].RegisterForOnPressed(pMouseInputComponent);
}

void MouseInputManager::RegisterComponentOnHeldKey(MouseInputComponent* pMouseInputComponent, const int& keyIndex)
{
	userInputKeys[keyIndex].RegisterForOnHeld(pMouseInputComponent);
}

void MouseInputManager::RegisterComponentOnReleasedKey(MouseInputComponent* pMouseInputComponent, const int& keyIndex)
{
	userInputKeys[keyIndex].RegisterForOnReleased(pMouseInputComponent);
}

void MouseInputManager::RegisterComponentOnPressedAction(MouseInputComponent* pMouseInputComponent, const int& actionIndex)
{
	userActions[actionIndex].RegisterForOnPressed(pMouseInputComponent);
}

void MouseInputManager::RegisterComponentOnHeldAction(MouseInputComponent* pMouseInputComponent, const int& actionIndex)
{
	userActions[actionIndex].RegisterForOnHeld(pMouseInputComponent);
}

void MouseInputManager::RegisterComponentOnReleasedAction(MouseInputComponent* pMouseInputComponent, const int& actionIndex)
{
	userActions[actionIndex].RegisterForOnReleased(pMouseInputComponent);
}

void MouseInputManager::DeregisterComponentOnPressedKey(MouseInputComponent* pMouseInputComponent, const int& keyIndex)
{
	userInputKeys[keyIndex].DeregisterFromOnPressed(pMouseInputComponent);
}

void MouseInputManager::DeregisterComponentOnHeldKey(MouseInputComponent* pMouseInputComponent, const int& keyIndex)
{
	userInputKeys[keyIndex].DeregisterFromOnHeld(pMouseInputComponent);
}

void MouseInputManager::DeregisterComponentOnReleasedKey(MouseInputComponent* pMouseInputComponent, const int& keyIndex)
{
	userInputKeys[keyIndex].DeregisterFromOnReleased(pMouseInputComponent);
}

void MouseInputManager::DeregisterComponentOnPressedAction(MouseInputComponent* pMouseInputComponent, const int& actionIndex)
{
	userActions[actionIndex].DeregisterFromOnPressed(pMouseInputComponent);
}

void MouseInputManager::DeregisterComponentOnHeldAction(MouseInputComponent* pMouseInputComponent, const int& actionIndex)
{
	userActions[actionIndex].DeregisterFromOnHeld(pMouseInputComponent);
}

void MouseInputManager::DeregisterComponentOnReleasedAction(MouseInputComponent* pMouseInputComponent, const int& actionIndex)
{
	userActions[actionIndex].DeregisterFromOnReleased(pMouseInputComponent);
}

void MouseInputManager::RegisterKeyMonitorToTracking(MouseKeyMonitor* pKeyMonitor)
{
	inputKeysToTrack.PushBack(pKeyMonitor, pKeyMonitor->GetStorageIterator());
}

void MouseInputManager::DeregisterKeyMonitorFromTracking(MouseKeyMonitor* pKeyMonitor)
{
	inputKeysToTrack.Remove(pKeyMonitor->GetStorageIterator());
}

void MouseInputManager::BindAction(const int& actionIndex, const ActionBindingSetting& actionBindingSetting)
{
	if (actionBindingSetting.actionBindingType == ActionBindingSetting::Type::Mouse)
	{
		userActions[actionIndex].BindToKey(&userInputKeys[actionBindingSetting.index]);
	}
	else
	{
		userActions[actionIndex].UnBindFromKey();
	}
}

void MouseInputManager::Initialize(MouseKeyMonitor& keyMonitor, const int& keyCode)
{
	keyMonitor.SetInputManager(this);
	keyMonitor.SetKeyCode(keyCode);
}
