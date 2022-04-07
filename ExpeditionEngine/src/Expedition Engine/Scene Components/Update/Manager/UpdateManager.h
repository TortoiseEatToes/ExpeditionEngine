#pragma once

#include "UpdateHeader.h"
#include "../../../../Expedition Resources/EngineSettings.h"

class UpdateManager
{
public:
	UpdateManager();
	UpdateManager(const UpdateManager& other) = delete;
	UpdateManager& operator= (const UpdateManager& other) = delete;
	~UpdateManager();

	/// <summary>This is called once per frame by the scene that owns this manager.</summary>
	void ProcessUpdateCalls();

	void Register(UpdateComponent* pUpdateComponent);
	void Deregister(UpdateComponent* pUpdateComponent);

private:

	void PushNodeIntoFreeList(UpdateHeader* pHeader);

	UpdateHeader updateHeaders[MaxNumberOfLiveUpdateComponents];
	UpdateHeader* pHeadFree = nullptr;
	UpdateHeader* pHeadUsed = nullptr;
	UpdateHeader* pTempHeader = nullptr;
};