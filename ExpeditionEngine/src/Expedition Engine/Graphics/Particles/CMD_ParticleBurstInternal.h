#pragma once

#include "ParticleBurstData.h"

//Used by the particle manager to store particle burst requests
class CMD_ParticleBurstInternal
{
public:
	CMD_ParticleBurstInternal() = default;
	CMD_ParticleBurstInternal(const CMD_ParticleBurstInternal&) = delete;
	CMD_ParticleBurstInternal(CMD_ParticleBurstInternal&&) = delete;
	CMD_ParticleBurstInternal& operator=(const CMD_ParticleBurstInternal&) = delete;
	CMD_ParticleBurstInternal& operator=(CMD_ParticleBurstInternal&&) = delete;
	~CMD_ParticleBurstInternal() = default;

	void SetData(const ParticleBurstData& initBurstData);
	const ParticleBurstData& GetData() const;

private:
	ParticleBurstData burstData;
};