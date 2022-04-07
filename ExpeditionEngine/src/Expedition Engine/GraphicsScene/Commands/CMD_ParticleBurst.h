#pragma once

#include "../../GraphicsScene/Commands/GraphicsSceneCommand.h"
#include "../../Graphics/Particles/ParticleBurstData.h"

class ParticleManager;
class GraphicsScene;

//The particle emmiters leave the commands on the particle manager to request a burst
class CMD_ParticleBurst : public GraphicsSceneCommand
{
public:
	CMD_ParticleBurst() = default;
	CMD_ParticleBurst(const CMD_ParticleBurst&) = delete;
	CMD_ParticleBurst(CMD_ParticleBurst&&) = delete;
	CMD_ParticleBurst& operator=(const CMD_ParticleBurst&) = delete;
	CMD_ParticleBurst& operator=(CMD_ParticleBurst&&) = delete;
	~CMD_ParticleBurst() = default;

	void SetData(const ParticleBurstData& otherParticleBurstData);
	const ParticleBurstData& GetData() const;

	void RecycleCommand() override;
	void Execute(GraphicsScene* pScene) override;

private:
	ParticleBurstData burstData;
};