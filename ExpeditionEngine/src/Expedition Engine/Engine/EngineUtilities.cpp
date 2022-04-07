#include "EngineUtilities.h"

#include "EngineUtilitiesTextLogger.h"

#include "../../Expedition Resources/EngineSettings.h"

void EngineUtilities::Print(const std::string & output)
{
	PushCommand(output);
}

void EngineUtilities::PrintDebugLog(const std::string& output)
{
#if EnableEngineThreadDebugLog
	PushCommand(output);
#endif //EnableEngineThreadDebugLog
}

void EngineUtilities::PrintSpeedTracking(const std::string& output)
{
#if EnableEngineThreadSpeedTracking
	PushCommand(output);
#endif //EnableEngineThreadSpeedTracking
}

void EngineUtilities::LogWarning(const std::string& output)
{
#if EnableWarningLog
	Instance()->PushWarning(output);
#endif
}

EngineUtilitiesTextLogger* EngineUtilities::Instance()
{
	static EngineUtilitiesTextLogger textLogger;
	return &textLogger;
}

void EngineUtilities::PushCommand(const std::string& output)
{
	//If we aren't printing anything, we shouldn't even create this object
#if PrintDebugTextToVSOutput
	Instance()->PushCommand(output);
#endif //PrintDebugTextToVSOutput
}

void EngineUtilities::EngineControl::ExecuteDebugCommands()
{
	//If we aren't printing anything, we shouldn't even create this object
#if PrintDebugTextToVSOutput
	Instance()->ExecuteDebugCommands();
#endif //PrintDebugTextToVSOutput
}

void EngineUtilities::EngineControl::PrintWarnings()
{
	Instance()->PrintWarnings();
}
