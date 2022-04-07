#pragma once

#include "UpdateComponent.h"

class UpdateComponentAttorney
{
public:
	struct ManagerControl
	{
	private:
		friend class UpdateManager;

		static UpdateHeader* GetHeader(UpdateComponent* pComponent)
		{
			return pComponent->GetHeader();
		}
		static void SetHeader(UpdateComponent* pComponent, UpdateHeader* pNewHeader)
		{
			pComponent->SetHeader(pNewHeader);
		}
	};
};