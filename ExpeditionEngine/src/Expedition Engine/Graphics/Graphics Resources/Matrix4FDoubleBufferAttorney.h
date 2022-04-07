#pragma once

#include "Matrix4FDoubleBuffer.h"


class Matrix4FDoubleBufferAttorney
{
public:
	class ManagerControl
	{
	private:
		friend class Matrix4FDoubleBufferManager;

		static void Synchronize(Matrix4FDoubleBuffer& pMatrix4FDoubleBuffer)
		{
			pMatrix4FDoubleBuffer.Synchronize();
		}
	};
};