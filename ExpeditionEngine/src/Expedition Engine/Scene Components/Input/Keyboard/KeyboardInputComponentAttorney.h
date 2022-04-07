#pragma once

#include "KeyboardInputComponent.h"

class KeyboardInputComponentAttorney
{
public:
	struct ManagerControl
	{
	private:
		friend class KeyboardInputManager;

		static void ExecuteOnPressed(KeyboardInputComponent* pComponent)
		{
			pComponent->OnKeyPressed();
		}

		static void ExecuteOnHeld(KeyboardInputComponent* pComponent)
		{
			pComponent->OnKeyHeld();
		}

		static void ExecuteOnKeyReleased(KeyboardInputComponent* pComponent)
		{
			pComponent->OnKeyReleased();
		}
	};

	struct MonitorParentControl
	{
	private:
		friend class KeyboardInputMonitorParent;

		static List<KeyboardInputComponent*>::Iterator& GetIteratorOnPressed(KeyboardInputComponent* pComponent)
		{
			return pComponent->GetIteratorOnPressed();
		}

		static List<KeyboardInputComponent*>::Iterator& GetIteratorOnHeld(KeyboardInputComponent* pComponent)
		{
			return pComponent->GetIteratorOnHeld();
		}

		static List<KeyboardInputComponent*>::Iterator& GetIteratorOnReleased(KeyboardInputComponent* pComponent)
		{
			return pComponent->GetIteratorOnReleased();
		}

		static void ExecuteOnPressed(KeyboardInputComponent* pComponent)
		{
			pComponent->OnKeyPressed();
		}

		static void ExecuteOnHeld(KeyboardInputComponent* pComponent)
		{
			pComponent->OnKeyHeld();
		}

		static void ExecuteOnReleased(KeyboardInputComponent* pComponent)
		{
			pComponent->OnKeyReleased();
		}
	};
};