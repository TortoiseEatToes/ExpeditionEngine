#include "ParticleTypeSwapperButton.h"
#include "../../Expedition Engine/Graphics/ParticleSystem/ParticleEmitter.h"

ParticleTypeSwapperButton::~ParticleTypeSwapperButton()
{
}

ParticleTypeSwapperButton::ParticleTypeSwapperButton(SceneName sceneToExistIn, Image * spriteImage, Rect * rectangle)
	: Button(sceneToExistIn, spriteImage, rectangle)
{
}

void ParticleTypeSwapperButton::OnMouseClicked()
{
	pe->DeregisterFromScene();
}

void ParticleTypeSwapperButton::OnMouseReleased()
{
	if (pe->GetType() == ParticleEmitter::EmitterType::ColorLightEmitter) {
		pe->SetEmitterTypeTexture(model, texture);
	}
	else {
		pe->SetEmitterTypeColorLight(model);
	}
	pe->RegisterToScene();
}
