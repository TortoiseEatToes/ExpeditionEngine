#pragma once

#include "UIElement.h"

#include "../../Graphics/Sprites/SpriteString.h"

class Text : public UIElement
{
public:
	Text() = delete;
	Text(SceneName sceneToExistIn, SpriteFont* font);
	Text(SceneName sceneToExistIn, SpriteFont* font, std::string str, int x, int y);
	Text(const Text& other) = delete;
	Text& operator= (const Text& other) = delete;
	~Text() = default;

	void StartDrawing(const SceneName& sceneToRegisterTo) override;
	void StopDrawing() override;

	int GetHeight();
	int GetWidth();
	void Set(const int& x, const int& y);
	void Set(SpriteFont* font, std::string str, int x, int y);
	void Set(std::string str);
	void SetFormat(char* A, ...);
	void SetLayer(const LayerName& layer) override;


private:
	SpriteString spriteString;
};