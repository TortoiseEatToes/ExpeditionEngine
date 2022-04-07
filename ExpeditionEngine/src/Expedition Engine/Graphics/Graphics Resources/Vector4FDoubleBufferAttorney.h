#pragma once

#include "Vector4FDoubleBuffer.h"


class Vector4FDoubleBufferAttorney
{
public:
	class ManagerControl
	{
	private:
		friend class Vector4FDoubleBufferManager;

		static void Synchronize(Vector4FDoubleBuffer& pVector4FDoubleBuffer)
		{
			pVector4FDoubleBuffer.Synchronize();
		}
	};
};