#pragma once

#include "EngineSubsystem.h"

class EngineSubsystemAttorney
{
public:
	class EngineSubsystemManagerControl
	{
	private:
		friend class EngineSubsystemManager;
		static List<EngineSubsystem>::Iterator& GetIterator(EngineSubsystem& subsystem) { return subsystem.GetIterator(); }
		static void Terminate (EngineSubsystem& subsystem) { return subsystem.Terminate(); }
	};
};