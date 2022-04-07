#include "CMD_ParticleBurst.h"
#include "../../GraphicsScene/GraphicsSceneManagerAttorney.h"

void CMD_ParticleBurst::Execute(GraphicsScene* pScene)
{
	pScene->GetParticleManager().PushParticleBurstRequest(burstData);
}

void CMD_ParticleBurst::RecycleCommand()
{
	GraphicsSceneManagerAttorney::Command_ParticleBurstControl::RecycleCommand(this);
}

void CMD_ParticleBurst::SetData(const ParticleBurstData& otherParticleBurstData)
{
	burstData = otherParticleBurstData;
}

const ParticleBurstData& CMD_ParticleBurst::GetData() const
{
	return burstData;
}