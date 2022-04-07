#include "ComponentRegistrationCommand.h"
#include "../SceneManagerAttorney.h"

void ComponentRegistrationCommand::Initialize(ComponentRegistrationActionStrategy* pNewAction, GameObject* pGameObject)
{
	pAction = pNewAction;
	pComponent.GameObject = pGameObject;
}

void ComponentRegistrationCommand::Initialize(ComponentRegistrationActionStrategy* pNewAction, UpdateComponent* pNewComponent)
{
	pAction = pNewAction;
	pComponent.Update = pNewComponent;
}

void ComponentRegistrationCommand::Initialize(ComponentRegistrationActionStrategy* pNewAction, AlarmComponent* pNewComponent)
{
	pAction = pNewAction;
	pComponent.Alarm = pNewComponent;
}

void ComponentRegistrationCommand::Initialize(ComponentRegistrationActionStrategy* pNewAction, KeyboardInputComponent* pNewComponent)
{
	pAction = pNewAction;
	pComponent.KeyboardInput = pNewComponent;
}

void ComponentRegistrationCommand::Initialize(ComponentRegistrationActionStrategy* pNewAction, MouseInputComponent* pNewComponent)
{
	pAction = pNewAction;
	pComponent.MouseInput = pNewComponent;
}

void ComponentRegistrationCommand::Initialize(ComponentRegistrationActionStrategy* pNewAction, SceneComponent* pNewComponent)
{
	pAction = pNewAction;
	pComponent.Scene = pNewComponent;
}

void ComponentRegistrationCommand::Execute(EngineScene* const pEngineScene)
{
	pAction->Execute(*pEngineScene, pComponent, attributeValue);
}

void ComponentRegistrationCommand::RecycleCommand()
{
	SceneManagerAttorney::CommandControl::RecycleCommand(this);
}
