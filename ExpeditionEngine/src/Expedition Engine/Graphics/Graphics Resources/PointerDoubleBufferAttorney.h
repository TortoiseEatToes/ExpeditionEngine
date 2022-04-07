#pragma once
#include "PointerDoubleBuffer.h"


class PointerDoubleBufferAttorney
{
public:
	class ManagerControl
	{
	private:
		friend class PointerDoubleBufferManager;

		static void Synchronize(PointerDoubleBuffer& pPointerDoubleBuffer)
		{
			pPointerDoubleBuffer.Synchronize();
		}
	};
};