#pragma once

#include "ParticleManager.h"

class ParticleManagerAttorney
{
public:
	struct GraphicsSceneControl
	{
	private:
		friend class GraphicsScene;

		static void ComputeAndRenderDX12(ParticleManager& particleManager, const Vector4F& cameraPosition)
		{
			particleManager.ComputeAndRenderDX12(cameraPosition);
		}
	};

};