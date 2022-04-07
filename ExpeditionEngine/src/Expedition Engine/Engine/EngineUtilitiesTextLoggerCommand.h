#pragma once

#include <string>

class EngineUtilitiesTextLoggerCommand
{
public:

	EngineUtilitiesTextLoggerCommand() = default;
	EngineUtilitiesTextLoggerCommand(const EngineUtilitiesTextLoggerCommand&) = delete;
	EngineUtilitiesTextLoggerCommand& operator= (const EngineUtilitiesTextLoggerCommand&) = delete;
	~EngineUtilitiesTextLoggerCommand() = default;

	std::string textToOutput;
};