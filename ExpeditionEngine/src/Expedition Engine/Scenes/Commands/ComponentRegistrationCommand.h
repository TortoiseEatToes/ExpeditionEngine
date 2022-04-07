#pragma once

#include "Registration Actions/ComponentRegistrationActionStrategy.h"
#include "SceneCommand.h"

class ComponentRegistrationCommand : public SceneCommand
{
public:
	ComponentRegistrationCommand() = default;
	ComponentRegistrationCommand(const ComponentRegistrationCommand& other) = delete;
	ComponentRegistrationCommand& operator= (const ComponentRegistrationCommand& other) = delete;
	~ComponentRegistrationCommand() = default;


	void Initialize(ComponentRegistrationActionStrategy* pNewAction, GameObject* pGameObject);
	void Initialize(ComponentRegistrationActionStrategy* pNewAction, UpdateComponent* pNewComponent);
	void Initialize(ComponentRegistrationActionStrategy* pNewAction, AlarmComponent* pNewComponent);
	void Initialize(ComponentRegistrationActionStrategy* pNewAction, KeyboardInputComponent* pNewComponent);
	void Initialize(ComponentRegistrationActionStrategy* pNewAction, MouseInputComponent* pNewComponent);
	void Initialize(ComponentRegistrationActionStrategy* pNewAction, SceneComponent* pNewComponent);

	void Execute(EngineScene* const pEngineScene) override;

	void RecycleCommand() override;

	ComponentRegistrationActionStrategy::Atribute attributeValue;

private:
	ComponentRegistrationActionStrategy* pAction;
	ComponentRegistrationActionStrategy::Component pComponent;
};