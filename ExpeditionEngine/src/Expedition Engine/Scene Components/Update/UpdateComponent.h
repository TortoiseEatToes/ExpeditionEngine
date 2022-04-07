#ifndef UPDATECOMPONENT_H
#define UPDATECOMPONENT_H

#include "Manager/UpdateHeader.h"
#include "../SceneComponent.h"

class UpdateComponent : public SceneComponent
{
public:
	UpdateComponent();
	UpdateComponent(const UpdateComponent& other) = delete;
	UpdateComponent& operator= (const UpdateComponent& other) = delete;
	virtual ~UpdateComponent();

	/// <summary>Stop calling OnUpdate every frame.</summary>
	virtual void OnUpdate() = 0;

	/// <summary>Stop calling OnUpdate every frame.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this object should register into</param>
	void StartUpdating(const SceneName& sceneToRegisterInto);

	/// <summary>Stop calling OnUpdate every frame.</summary>
	void StopUpdating();

protected:
	//OnUpdate should be in here

private:
	friend class UpdateComponentAttorney;

	void RegisterIntoSceneChild(EngineScene& engineScene) override;
	void DeregisterFromSceneChild(EngineScene& engineScene) override;

	UpdateHeader* pHeader = nullptr;

	UpdateHeader* GetHeader()
	{
		return pHeader;
	}
	void SetHeader(UpdateHeader* pNewHeader)
	{
		pHeader = pNewHeader;
	}
};

#endif // !UPDATEABLE_H