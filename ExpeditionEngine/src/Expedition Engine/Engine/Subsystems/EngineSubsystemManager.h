#pragma once

#include "../../Containers/List.h"

class EngineSubsystem;

class EngineSubsystemManager
{
public:
	EngineSubsystemManager();
	~EngineSubsystemManager();

	//Push a
	void RegisterSubsystem(EngineSubsystem& subsystem);
	void DeregisterSubsystem(EngineSubsystem& subsystem);

	int NumberOfActiveSubsystems() { return activeSubsystems.GetSize(); }
	size_t SizeOfAllocatedSubSystems();
	
private:
	List<EngineSubsystem> activeSubsystems;
	List<EngineSubsystem>::Iterator iterator;
};