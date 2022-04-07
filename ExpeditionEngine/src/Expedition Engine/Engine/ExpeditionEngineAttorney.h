#ifndef EXPEDITIONENGINEATTORNEY_H
#define EXPEDITIONENGINEATTORNEY_H

#include "ExpeditionEngine.h"

#include <iostream>

class ExpeditionEngineAttorney
{
public:
	class MainCalls
	{
	private:
		friend int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow);

		static void RunGame(HWND& hwnd)
		{
			ExpeditionEngine::RunGame(hwnd);
		}

		static void Terminate()
		{
			ExpeditionEngine::Terminate();
		}

		static void Initialize() 
		{
			ExpeditionEngine::Initialize();
		}
	};

	class CommandCalls
	{
	private:
		friend class CommandQuit;

		static void Quit()
		{
			ExpeditionEngine::Quit();
		}
	};

	class ResolveFrameControl
	{
	private:
		friend class Task_ResolveFrame;

		static void ExecuteCommandQueue()
		{
			ExpeditionEngine::ExecuteCommandQueue();
		}

		static void ProcessMessages()
		{
			ExpeditionEngine::ProcessMessages();
		}
	};

	class MainLoopEndControl
	{
		friend class Task_MainLoopEnd;

		static void WakeMainThread()
		{
			ExpeditionEngine::WakeMainThread();
		}
	};
};

#endif // !EXPEDITIONENGINEATTORNEY_H
