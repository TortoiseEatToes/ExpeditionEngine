#ifndef EXPEDITIONENGINE_H
#define EXPEDITIONENGINE_H

#include "Threads/ThreadManager.h"
#include "Tasks/TaskManager.h"

#include "../Containers/Containers.h"
#include "Commands/CommandQuit.h"

#include "../DX12App/DXApp/DXApp_12.h"

#include "../Time/StopwatchFloat.h"

class ExpeditionEngine
{
public:
	/// <summary>Shut down the game and the engine.</summary>
	static void Quit()
	{
		Instance().privQuit();
	}

	/// <summary>Return the width of the window.</summary>
	/// <returns>float copy of the window width</returns>
	static float GetWidth() 
	{
		return DXApp_12::GetWidth();
	}

	/// <summary>Return the height of the window.</summary>
	/// <returns>float copy of the window height</returns> 
	static float GetHeight()
	{
		return DXApp_12::GetHeight();
	}

private:
	friend class ExpeditionEngineAttorney;

	ExpeditionEngine();
	ExpeditionEngine(const ExpeditionEngine&) = delete;
	ExpeditionEngine& operator= (const ExpeditionEngine&) = delete;
	~ExpeditionEngine();

	/// <summary>Create all of the memory that is owned by this singleton.  This has to be done before the game has started.</summary>
	static void Initialize()
	{
		pInstance = new ExpeditionEngine();
	};
	/// <summary>Destroy all of the memory that is owned by this singleton.  This should only be done once the game has been shut down.</summary>
	static void Terminate()
	{
		delete pInstance;
	}
	
	/// <summary>Get a reference to instance of the Expedition Engine.</summary>
	/// <returns>Referene to the instance of this manager</returns>
	static ExpeditionEngine& Instance()
	{
		return *pInstance;
	}

	/// <summary>//Start running a game instance starting at LoadResources and ending at UnloadResources. NOTE: This will run forever until the QuitGame function is called</summary>
	/// <param name="hwnd">Reference to the windows handle that the DXApp needs</param>
	static void RunGame(HWND& hwnd)
	{
		Instance().privRunGame(hwnd);
	}
	void privRunGame(HWND& hwnd);

	/// <summary>Execute all of the commands that were passed to the engine.</summary>
	static void ExecuteCommandQueue()
	{
		Instance().privExecuteCommandQueue();
	}
	void privExecuteCommandQueue();

	/// <summary>Process windows messages. NOTE: SARA BELIVES THAT THIS MUST BE PROCESSED BY THE MAIN THREAD</summary>
	static void ProcessMessages()
	{
		Instance().privProcessMessages();
	}
	void privProcessMessages();

	static void WakeMainThread()
	{
		Instance().privWakeMainThread();
	}
	void privWakeMainThread();
	void MarkMainLoopAsStarted();
	void SleepMainThread();

	//----------------------- USER FUNCTIONS ----------------------------------------------
	/// <summary>The user uses this function to load all of the outside resources that they need for the game.</summary>
	void LoadResources();
	/// <summary>The user uses this function to define what should happen when the game has just started.</summary>
	void StartGame();
	/// <summary>The user uses this function to define what should happen when the game has just ended.</summary>
	void EndGame();
	/// <summary>The user uses this function to unload any outside resources that they needed for the game.</summary>
	void UnloadResources();
	//----------------------- END USER FUNCTIONS ----------------------------------------------

	/// <summary>Private function that is used to create all of the singletons that the engine needs.</summary>
	void InitializeSingletons(HWND& hwnd);
	/// <summary>Private function that is used to destroy all of the singletons that the initialize singletons created.</summary>
	void TerminateSingletons();

	void privQuit();

	void SetupGame();

	void ExecuteMainLoop();
	void ShutdownGame();
	void ReportFinalEngineSpeeds();

	Queue<EngineCommand*> commandQueue;
	CommandQuit commandQuit;
	TaskManager taskManager;
	static ExpeditionEngine* pInstance;

	std::condition_variable conditionalVariable;
	std::mutex mutex;
	std::atomic_bool isExecutingTask = false;

	StopwatchFloat gameTimer;
	StopwatchFloat currentSecondTimer;
	StopwatchFloat frameTimer;
	float currentFrameTime = 0.0f;
	float totalFrameTime = 0.0f;
	int framesThisSecond = 0;
	int totalNumberOfFrames = 0;

	//Used for the PeekMessage loop
	MSG msg = { 0 };
	bool isEngineRunning = true;
	
	const float targetFrameTime = 1.0f / static_cast<float>(targetFPS);
};

#endif // !EXPEDITIONENGINE_H