#include "EngineSubsystemManager.h"

#include "EngineSubsystemAttorney.h"

#include <assert.h>

EngineSubsystemManager::EngineSubsystemManager()
{
}

EngineSubsystemManager::~EngineSubsystemManager()
{
	assert(activeSubsystems.GetSize() == 0);
}

void EngineSubsystemManager::RegisterSubsystem(EngineSubsystem& subsystem)
{
	activeSubsystems.PushFront(subsystem, EngineSubsystemAttorney::EngineSubsystemManagerControl::GetIterator(subsystem));
}

void EngineSubsystemManager::DeregisterSubsystem(EngineSubsystem & subsystem)
{
	activeSubsystems.Remove(EngineSubsystemAttorney::EngineSubsystemManagerControl::GetIterator(subsystem));
}

size_t EngineSubsystemManager::SizeOfAllocatedSubSystems()
{
	size_t result = 0;
	activeSubsystems.SetFront(iterator);
	while (!iterator.IsOutOfNodes())
	{
		result += iterator.GetCurrentObject().ActiveMemory();
		++iterator;
	}
	return result;
}
