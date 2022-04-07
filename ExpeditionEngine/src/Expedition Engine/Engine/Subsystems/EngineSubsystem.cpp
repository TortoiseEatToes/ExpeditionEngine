#include "EngineSubsystem.h"

#include "../ExpeditionEngineAttorney.h"

EngineSubsystem::EngineSubsystem()
{
	ExpeditionEngineAttorney::SubsystemControl::RegisterSubsystem(*this);
}

EngineSubsystem::~EngineSubsystem()
{
	//It is possible that this manager was terminated earlier
	if (!iterator.IsOutOfNodes())
	{
		ExpeditionEngineAttorney::SubsystemControl::DeregisterSubsystem(*this);
	}
}