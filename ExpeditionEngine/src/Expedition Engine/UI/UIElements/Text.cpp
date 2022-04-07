#include "Text.h"


Text::Text(SceneName sceneToExistIn, SpriteFont* font)
	: spriteString(sceneToExistIn, font)
{

}

Text::Text(SceneName sceneToExistIn, SpriteFont* font, std::string str, int x, int y)
	: spriteString(sceneToExistIn, font, str, x, y)
{

}

void Text::StartDrawing(const SceneName& sceneToRegisterTo)
{
	spriteString.StartDrawing();
}

void Text::StopDrawing()
{
	spriteString.StopDrawing();
}

int Text::GetHeight()
{
	return spriteString.GetHeight();
}

int Text::GetWidth()
{
	return spriteString.GetWidth();
}

void Text::Set(const int& x, const int& y)
{
	spriteString.Set(x, y);
}

void Text::Set(SpriteFont* font, std::string str, int x, int y)
{
	spriteString.Set(font, str, x, y);
}

void Text::Set(std::string str)
{
	spriteString.Set(str);
}

void Text::SetFormat(char* A, ...)
{
	//spriteString.SetFormat()
}

void Text::SetLayer(const LayerName& layer)
{
	spriteString.SetLayer(layer);
}
