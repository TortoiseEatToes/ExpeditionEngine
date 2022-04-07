#pragma once

#include "../../Expedition Engine/UI/UIElements/Button.h"

class ParticleEmitter;
class Model;
class Texture;

class ParticleTypeSwapperButton : public Button
{
public:
	ParticleTypeSwapperButton() = delete;
	ParticleTypeSwapperButton(ParticleTypeSwapperButton&&) = delete;
	ParticleTypeSwapperButton(const ParticleTypeSwapperButton&) = delete;
	const ParticleTypeSwapperButton& operator = (ParticleTypeSwapperButton&&) = delete;
	const ParticleTypeSwapperButton& operator = (const ParticleTypeSwapperButton&) = delete;
	~ParticleTypeSwapperButton();

	ParticleTypeSwapperButton(SceneName sceneToExistIn, Image* spriteImage, Rect* rectangle);

	ParticleEmitter* pe;
	Model* model;
	Texture* texture;
	SceneName sceneName;

private:
	void OnMouseClicked() override;
	void OnMouseReleased() override;

};

