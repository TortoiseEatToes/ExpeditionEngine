#include "CommandQuit.h"

#include "../ExpeditionEngineAttorney.h"

void CommandQuit::Execute()
{
	ExpeditionEngineAttorney::CommandCalls::Quit();
}