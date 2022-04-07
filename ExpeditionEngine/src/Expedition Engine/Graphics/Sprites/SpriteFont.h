#ifndef SpriteFont_h
#define SpriteFont_h

#include "SpriteData.h"
#include <map>
#include "RapidXML/rapidxml.hpp"
#include "../../../Expedition Resources/TextureSettings.h"

class SpriteFont
{
public:
	SpriteFont() = delete;
	~SpriteFont();
	SpriteFont(const SpriteFont&) = delete;
	SpriteFont& operator = (const SpriteFont&) = delete;

	using Key = int;
	using Glyph = SpriteData;

private:
	Texture* FontTexture;
	using FontMap = std::map< Key, Glyph* >;
	FontMap fontmap;

	std::string Name;

	void XMLtoCollection(std::string path);

	void CreateGlyph(rapidxml::xml_node<char>* node);

	Image** imgArray;

	int size;

public:
	SpriteFont(TextureName name, const wchar_t* path);
	Glyph* GetGlyph(char c);
};

#endif SpriteFont_h