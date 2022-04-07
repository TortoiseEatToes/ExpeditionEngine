#pragma once

#include "../../Containers/List.h"

/// <summary>Inherit from this parent class to allow the ExpeditionEngine to get performance tracking on your subsystem.</summary>
class EngineSubsystem
{
public:
	EngineSubsystem();
	virtual ~EngineSubsystem();

	/// <summary>Get the total amount of memory that this subsystem used over it's lifetime.</summary>
	size_t TotalAllocatedMemory() { return allocatedBytes; }

	/// <summary>Get the amount of memory that this subsystem is currently using.</summary>
	size_t ActiveMemory() { return allocatedBytes - deallocatedBytes; }

protected:
	/// <summary>Override this so that your subsystem can be destroyed when the engine shuts down.</summary>
	virtual void Terminate() = 0;

	/// <summary>Call this whenever you call new on an object owned by this subsystem.</summary>
	void AllocateBytes(const size_t& allocatedBytes) { this->allocatedBytes += allocatedBytes; }

	/// <summary>Call this whenever you call delete on an object owned by this subsystem.</summary>
	void DeallocateBytes(const size_t& deallocatedBytes) { this->deallocatedBytes += deallocatedBytes; }


private:
	friend class EngineSubsystemAttorney;

	List<EngineSubsystem>::Iterator& GetIterator() { return iterator; }

	List<EngineSubsystem>::Iterator iterator;
	size_t allocatedBytes = 0;
	size_t deallocatedBytes = 0;
};