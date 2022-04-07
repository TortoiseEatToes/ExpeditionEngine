#include "Task_RenderParticles.h"

#include "../../GraphicsScene/GraphicsSceneManagerAttorney.h"

Task_RenderParticles::Task_RenderParticles()
	: EngineTask("Render Particles", EngineTask::PriorityLevel::High)
{
	//Do nothing
}

void Task_RenderParticles::Work()
{
	GraphicsSceneManagerAttorney::RenderParticlesControl::RenderParticles();
}
