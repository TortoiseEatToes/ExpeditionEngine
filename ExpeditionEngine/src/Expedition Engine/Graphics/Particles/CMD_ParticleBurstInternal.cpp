#include "CMD_ParticleBurstInternal.h"

void CMD_ParticleBurstInternal::SetData(const ParticleBurstData& initBurstData)
{
	burstData = initBurstData;
}

const ParticleBurstData& CMD_ParticleBurstInternal::GetData() const
{
	return burstData;
}
