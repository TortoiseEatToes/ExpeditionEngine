#pragma once

#include "../../Expedition Engine/Scene Components/Update/UpdateComponent.h"
#include "../../Expedition Engine/Math/Vector/Vector4F.h"

class Update_FlashLight : public UpdateComponent
{
public:

	Vector4F amb = Vector4F(0.0f, 0.0f, 0.0f, 1.0f);
	Vector4F diff = Vector4F(2.0f, 2.0f, 2.0f, 1.0f);
	Vector4F spec = Vector4F(2.0f, 2.0f, 2.0f, 0.8f);

private:
	// Inherited via UpdateComponent
	virtual void OnUpdate() override;
};