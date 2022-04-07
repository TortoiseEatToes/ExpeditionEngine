#include "UpdateManager.h"

#include "../UpdateComponentAttorney.h"

#include <cassert>

UpdateManager::UpdateManager()
{
	pHeadFree = &updateHeaders[0];
	pTempHeader = pHeadFree;

	unsigned int counter = 1;
	while (counter < MaxNumberOfLiveUpdateComponents)
	{
		pTempHeader->pNext = &updateHeaders[counter];
		pTempHeader->pNext->pPrevious = pTempHeader;

		pTempHeader = pTempHeader->pNext;
		++counter;
	}
}

void UpdateManager::ProcessUpdateCalls()
{
	pTempHeader = pHeadUsed;
	while (pTempHeader != nullptr)
	{
		pTempHeader->pComponent->OnUpdate(); 
		pTempHeader = pTempHeader->pNext;
	}
}

void UpdateManager::Register(UpdateComponent* pUpdateComponent)
{
	assert(pHeadFree != nullptr && "NOT ENOUGH UPDATE HEADERS");
	
	//Grab a free header
	pTempHeader = pHeadFree;
	if (pHeadFree->pNext != nullptr)
	{
		pHeadFree->pNext->pPrevious = nullptr;
		pHeadFree = pHeadFree->pNext;
	}
	else
	{
		pHeadFree = nullptr;
	}

	//Push node into used list	
	if (pHeadUsed != nullptr)
	{
		pHeadUsed->pPrevious = pTempHeader;
		pTempHeader->pNext = pHeadUsed;
		pTempHeader->pPrevious = nullptr;
	}
	else
	{
		pTempHeader->pNext = nullptr;
		pTempHeader->pPrevious = nullptr;
	}

	pHeadUsed = pTempHeader;

	pTempHeader->pComponent = pUpdateComponent;

	UpdateComponentAttorney::ManagerControl::SetHeader(pUpdateComponent, pTempHeader);
}

void UpdateManager::Deregister(UpdateComponent* pUpdateComponent)
{
	pTempHeader = UpdateComponentAttorney::ManagerControl::GetHeader(pUpdateComponent);

	if (pTempHeader->pPrevious == nullptr)
	{
		//Only header in the list
		if (pTempHeader->pNext == nullptr)
		{
			pHeadUsed = nullptr;

			//We can safely assume that the free header is full
			pHeadFree->pPrevious = pTempHeader;
			pTempHeader->pNext = pHeadFree;

			pHeadFree = pTempHeader;
		}
		else //Front of list, but not alone
		{
			pTempHeader->pNext->pPrevious = nullptr;
			pHeadUsed = pTempHeader->pNext;

			if (pHeadFree != nullptr)
			{
				pHeadFree->pPrevious = pTempHeader;
				pTempHeader->pNext = pHeadFree;
			}
			else
			{
				pTempHeader->pNext = nullptr;
			}

			pHeadFree = pTempHeader;
		}
	}
	else
	{
		//back of the list
		if (pTempHeader->pNext == nullptr)
		{
			//Remove from used headers
			pTempHeader->pPrevious->pNext = nullptr;

			//Push into free headers
			if (pHeadFree != nullptr)
			{
				pHeadFree->pPrevious = pTempHeader;
				pTempHeader->pNext = pHeadFree;
				pTempHeader->pPrevious = nullptr;
			}
			else
			{
				pHeadFree = pTempHeader;
				pTempHeader->pPrevious = nullptr;
			}
		}
		else //Middle of the list
		{
			//Remove from used headers
			pTempHeader->pNext->pPrevious = pTempHeader->pPrevious;
			pTempHeader->pPrevious->pNext = pTempHeader->pNext;

			//Push into Free Headers
			if (pHeadFree != nullptr)
			{
				pHeadFree->pPrevious = pTempHeader;
				pTempHeader->pNext = pHeadFree;
				pTempHeader->pPrevious = nullptr;
			}
			else
			{
				pHeadFree = pTempHeader;
				pTempHeader->pNext = nullptr;
				pTempHeader->pPrevious = nullptr;
			}
		}
	}

	PushNodeIntoFreeList(pTempHeader);
	UpdateComponentAttorney::ManagerControl::SetHeader(pUpdateComponent, nullptr);
}

void UpdateManager::PushNodeIntoFreeList(UpdateHeader* pHeader)
{
	if (pHeadFree != nullptr)
	{
		pHeadFree->pPrevious = pHeader;
		pHeader->pNext = pHeadFree;
		pHeader->pPrevious = nullptr;
	}
	else
	{
		pHeadFree = pHeader;
		pHeader->pNext = nullptr;
		pHeader->pPrevious = nullptr;
	}
}

UpdateManager::~UpdateManager()
{
}