#pragma once

class EngineUtilitiesTextLogger;

#include <string>

class EngineUtilities
{
private:
	static void PushCommand(const std::string& output);

	static EngineUtilitiesTextLogger* Instance();

public:
	class EngineControl
	{
	private:
		friend class ExpeditionEngine;

		static void ExecuteDebugCommands();
		static void PrintWarnings();
	};

	/// <summary>Use this for engine systems to print text.</summary>
/// <param name="output">The char string that you want to print.</param>
	static void Print(const std::string& output);

	/// <summary>Use this for engine systems to print text output only when EnableEngineThreadDebugLog is true.</summary>
	/// <param name="output">The char string that you want to print.</param>
	static void PrintDebugLog(const std::string& output);

	/// <summary>Use this for engine systems to print text output only when EnableEngineThreadSpeedTracking is true.</summary>
	/// <param name="output">The char string that you want to print.</param>
	static void PrintSpeedTracking(const std::string& output);


	/// <summary>Used for when the engine needs to throw a warning to the user.</summary>
	/// <param name="output">The char string that you want to print.</param>
	static void LogWarning(const std::string& output);
};