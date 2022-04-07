#pragma once

#include "CameraDataDoubleBuffer.h"

class CameraDataDoubleBufferAttorney
{
public:

	class ManagerControl
	{
	private:
		friend class CameraDataManager;

		static void Synchronize(CameraDataDoubleBuffer& doubleBuffer)
		{
			doubleBuffer.Synchronize();
		}
	};

	class StateControl
	{
	private:
		friend class CameraDataDoubleBufferStateDirty;

		static void Synchronize(CameraDataDoubleBuffer* const pDoubleBuffer)
		{
			pDoubleBuffer->StateCall_Synchronize();
		}
	};
};