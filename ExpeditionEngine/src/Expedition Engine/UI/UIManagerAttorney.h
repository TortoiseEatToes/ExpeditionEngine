#pragma once

#include "UIManager.h"

class UIManagerAttorney
{
public:

	class EngineControl
	{
	private:
		friend class ExpeditionEngine;

		static void Initialize()
		{
			UIManager::Initialize();
		}

		static void Terminate()
		{
			UIManager::Terminate();
		}
	};

	class DrawFrameControl
	{
	private:
		friend class Task_DrawFrame;

		static void DrawUI()
		{
			UIManager::DrawUI();
		}
	};
};