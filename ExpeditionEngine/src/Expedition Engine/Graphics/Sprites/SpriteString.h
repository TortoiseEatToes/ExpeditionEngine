#ifndef SpriteString_h
#define SpriteString_h

#include "../../Containers/List.h"
#include <string>
#include "../../../Expedition Resources/SceneSettings.h"
#include "../../../Expedition Resources/LayerSettings.h"

class SpriteFont;
class GraphicsObject_Sprite;

class SpriteString
{
public:
	SpriteString();
	SpriteString(SceneName sceneToExistIn, SpriteFont* font);
	SpriteString(SceneName sceneToExistIn, SpriteFont* font, std::string str, int x, int y);
	~SpriteString();
	SpriteString(const SpriteString&) = delete;
	SpriteString& operator = (const SpriteString&) = delete;

private:
	void ClearList();

	using Glyph = GraphicsObject_Sprite;
	using GlyphCollection = List<Glyph>;

	GlyphCollection glyphs;

	int height;
	int width;
	int posX;
	int posY;

	SpriteFont* pFont;

	SceneName sceneName;

	static const int BUFF_SIZE = 256;
	static char DebugBuff[BUFF_SIZE];

public:
	int GetHeight() { return height; }
	int GetWidth() { return width; }
	void Set(const int& x, const int& y);
	void Set(SpriteFont* font, std::string str, int x, int y);
	void Set(std::string str);
	void SetFormat(char* A, ...);
	void SetLayer(const LayerName& layer);

	void StartDrawing();
	void StopDrawing();

};

#endif SpriteString_h