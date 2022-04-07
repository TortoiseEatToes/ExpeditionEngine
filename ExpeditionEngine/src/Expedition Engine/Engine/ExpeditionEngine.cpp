#include "ExpeditionEngine.h"

ExpeditionEngine* ExpeditionEngine::pInstance = nullptr;

#include "Threads/ThreadManagerAttorney.h"
#include "../Time/EngineTimeAttorney.h"
#include "../Scene Components/Input/Manager/InputManagerAttorney.h"
#include "../Scenes/SceneManagerAttorney.h"
#include "../GraphicsScene/GraphicsSceneManagerAttorney.h"
#include "../Graphics/Model/Managers/ModelManagerAttorney.h"
#include "../Graphics/Model/Managers/TextureManagerAttorney.h"
#include "../Graphics/Image/ImageManagerAttorney.h"
#include "../Graphics/Sprites/Manager/SpriteFontManagerAttorney.h"
#include "../Scene Components/Collision/Manager/CollisionSystemAttorney.h"
#include "../Graphics/Sprites/Manager/SpriteFontManagerAttorney.h"

#include "../Audio/Clips/AudioClipManagerAttorney.h"
#include "../Audio/AudioSystemAttorney.h"


#include "../DX12App/DXApp/DXApp_12.h"
#include "../DX12App/Shaders/ShaderManager_12.h"

#include "../Graphics/Terrain/TerrainObjectManager.h"

#include "../UI/UIManagerAttorney.h"

#include "EngineUtilities.h"

#include <thread>
#include <chrono>



ExpeditionEngine::ExpeditionEngine()
{

}

void ExpeditionEngine::InitializeSingletons(HWND& hwnd)
{
	//Initialize Engine
#if EnableMultiThreading
	ThreadManagerAttorney::EngineControl::Initialize();
	ThreadManagerAttorney::EngineControl::InitializeThreads();
#endif //EnableMultiThreading

	EngineTimeAttorney::EngineControl::Initialize();

	DXApp_12::Initialize(hwnd);

	//Initialize Graphics objects

	//UIManagerAttorney::EngineControl::Initialize();
	GraphicsSceneManagerAttorney::EngineControl::Initialize();

	AudioSystemAttorney::EngineControl::Initialize();
	AudioClipManagerAttorney::EngineControl::Initialize();

	//Initialize Scene
	InputManagerAttorney::EngineControl::Initialize();
	CollisionSystemAttorney::EngineControl::Initialize();
	SceneManagerAttorney::EngineControl::Initialize();
}

void ExpeditionEngine::privExecuteCommandQueue()
{
	while (commandQueue.GetSize() > 0)
	{
		commandQueue.Pop()->Execute();
	}
}

void ExpeditionEngine::privProcessMessages()
{
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void ExpeditionEngine::privRunGame(HWND& hwnd)
{
	InitializeSingletons(hwnd);
	LoadResources();


	DXApp_12::DoneUploadingResources();
	DXApp_12::PrepareToRender();


	SetupGame();

	gameTimer.Start();
	currentSecondTimer.Start();
	while (isEngineRunning)
	{
		ExecuteMainLoop();
	}
	gameTimer.Stop();

	ShutdownGame();
	ReportFinalEngineSpeeds();

	//taskManager.PrintTaskFamilyTree();

	EngineUtilities::EngineControl::ExecuteDebugCommands();
	EngineUtilities::EngineControl::PrintWarnings();
}

void ExpeditionEngine::TerminateSingletons()
{
	DXApp_12::StartCleanup();

	AudioSystem::StopAllSounds();
	AudioSystemAttorney::EngineControl::FinalExecution();

	//Terminate Scene
	SceneManagerAttorney::EngineControl::Terminate();
	CollisionSystemAttorney::EngineControl::Terminate();
	InputManagerAttorney::EngineControl::Terminate();

	//Terminate Graphics objects
	GraphicsSceneManagerAttorney::EngineControl::Terminate();
	//UIManagerAttorney::EngineControl::Terminate();

	AudioClipManagerAttorney::EngineControl::Terminate();
	AudioSystemAttorney::EngineControl::Terminate();

	//Terminate Asset Managers
	ModelManagerAttorney::Engine::Terminate();
	TextureManagerAttorney::Engine::Terminate();
	ImageManagerAttorney::Engine::Terminate();
	//SpriteFontManagerAttorney::Engine::Terminate();
	TerrainObjectManager::Terminate();

	//TextureManagerAttorney_12::Engine::Terminate();


	DXApp_12::Terminate();

	//Terminate Engine
	EngineTimeAttorney::EngineControl::Terminate();
#if EnableMultiThreading
	ThreadManagerAttorney::EngineControl::Terminate();
#endif //EnableMultiThreading
}

void ExpeditionEngine::privQuit()
{
	isEngineRunning = false;
}

void ExpeditionEngine::SetupGame()
{
	//Process time once to make sure everything starts off alright.
	EngineTimeAttorney::EngineControl::ProcessTime();

	StartGame();
	SceneManagerAttorney::EngineControl::StartFirstScene();

	EngineUtilities::PrintDebugLog("\n\n--------------- ENGINE IS STARTING TO RUN DEBUG LOG ----------------- \n\n");
	EngineUtilities::PrintSpeedTracking("\n\n--------------- ENGINE IS STARTING TO RUN PERFORMANCE TRACKING ----------------- \n\n");
}

void ExpeditionEngine::ExecuteMainLoop()
{
	if (framesThisSecond * targetFrameTime <= currentSecondTimer.Peak())
	{
		++totalNumberOfFrames;
		++framesThisSecond;

		EngineUtilities::PrintDebugLog("\n\n---------------Current number of frames: " + std::to_string(totalNumberOfFrames) + "------------------------\n\n");

		frameTimer.Start();
#if EnableMultiThreading
		MarkMainLoopAsStarted();
#endif
		taskManager.ExecuteTasks();
		privProcessMessages();
#if EnableMultiThreading
		SleepMainThread();
#endif
		currentFrameTime = frameTimer.Stop();
		totalFrameTime += currentFrameTime;
		
		EngineUtilities::PrintSpeedTracking(std::string("\n\nFrame complete! Total time to comeplete frame: ") + std::to_string(currentFrameTime).c_str() + "\n");
		EngineUtilities::EngineControl::ExecuteDebugCommands();

		if (currentSecondTimer.Peak() >= 1.0f)
		{
			EngineUtilities::PrintSpeedTracking(std::string("\nOne second has past! Current FPS: ") + std::to_string(framesThisSecond).c_str() + "\n");
			framesThisSecond = 0;
			currentSecondTimer.Stop();
			currentSecondTimer.Start();
		}
	}
}

void ExpeditionEngine::ShutdownGame()
{
	EngineUtilities::PrintDebugLog("\n\n--------------- ENGINE IS SHUTTING DOWN ----------------- \n\n");
	EngineUtilities::EngineControl::ExecuteDebugCommands();

	EndGame();
	UnloadResources();
	TerminateSingletons();

	EngineUtilities::PrintDebugLog("\n\n--------------- ENGINE SUCCESSFULLY SHUT DOWN ----------------- \n\n");
}

void ExpeditionEngine::ReportFinalEngineSpeeds()
{
	EngineUtilities::PrintSpeedTracking("\n--------------- START AVERAGE FRAME TIME -----------------\n");
	taskManager.ReportAverageSpeed();

	EngineUtilities::PrintSpeedTracking("\n\nAverage Time taken by frame: " + std::to_string(totalFrameTime / static_cast<float>(totalNumberOfFrames)));

	if (gameTimer.GetElapsedTime() > 1.0f)
	{
		EngineUtilities::PrintSpeedTracking("\nAverage FPS: " + std::to_string(static_cast<float>(totalNumberOfFrames / gameTimer.GetElapsedTime())));
	}
	else
	{
		EngineUtilities::PrintSpeedTracking("\nAverage FPS: " + std::to_string(static_cast<float>(totalNumberOfFrames)));
	}
	
	EngineUtilities::PrintSpeedTracking("\n\n--------------- END AVERAGE FRAME TIME ----------------- \n\n");
}

ExpeditionEngine::~ExpeditionEngine()
{
	//Do nothing
}

void ExpeditionEngine::privWakeMainThread()
{
	std::lock_guard<std::mutex> lock(mutex);
	isExecutingTask = false;
	conditionalVariable.notify_all();
}

void ExpeditionEngine::MarkMainLoopAsStarted()
{
	isExecutingTask = true;
}

void ExpeditionEngine::SleepMainThread()
{
	std::unique_lock<std::mutex> lock(mutex);
	conditionalVariable.wait(lock, [this] {return !isExecutingTask; });
}
