#pragma once

#include "MouseInputComponent.h"

class MouseInputComponentAttorney
{
public:
	struct ManagerControl
	{
	private:
		friend class MouseInputManager;

		static void ExecuteOnPressed(MouseInputComponent* pComponent)
		{
			pComponent->OnPressed();
		}

		static void ExecuteOnHeld(MouseInputComponent* pComponent)
		{
			pComponent->OnHeld();
		}

		static void ExecuteOnReleased(MouseInputComponent* pComponent)
		{
			pComponent->OnReleased();
		}
	};

	struct MonitorParentControl
	{
	private:
		friend class MouseInputMonitorParent;

		static List<MouseInputComponent*>::Iterator& GetIteratorOnPressed(MouseInputComponent* pComponent)
		{
			return pComponent->GetIteratorOnPressed();
		}

		static List<MouseInputComponent*>::Iterator& GetIteratorOnHeld(MouseInputComponent* pComponent)
		{
			return pComponent->GetIteratorOnHeld();
		}

		static List<MouseInputComponent*>::Iterator& GetIteratorOnReleased(MouseInputComponent* pComponent)
		{
			return pComponent->GetIteratorOnReleased();
		}

		static void ExecuteOnPressed(MouseInputComponent* pComponent)
		{
			pComponent->OnPressed();
		}

		static void ExecuteOnHeld(MouseInputComponent* pComponent)
		{
			pComponent->OnHeld();
		}

		static void ExecuteOnReleased(MouseInputComponent* pComponent)
		{
			pComponent->OnReleased();
		}
	};
};