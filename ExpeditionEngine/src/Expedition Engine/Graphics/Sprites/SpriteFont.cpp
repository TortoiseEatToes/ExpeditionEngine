#include "SpriteFont.h"
#include "RapidXML/rapidxml_utils.hpp"
#include "../Image/ImageManager.h"
#include "../Model/Managers/TextureManager.h"
#include "SpriteFactory/SpriteFactory.h"
#include "../../../Expedition Resources/SceneSettings.h"

SpriteFont::~SpriteFont()
{
	for (int i = 0; i < size; ++i) {
		if (imgArray[i])
			delete imgArray[i];
	}

	FontMap::iterator it =  fontmap.begin();

	while ((it != fontmap.end())) {
		delete (*it).second;
		++it;
	}
	

	delete[] imgArray;
}


SpriteFont::SpriteFont(TextureName Name, const wchar_t* path)
{
	std::wstring ws(path);

	std::wstring tmp = ( ws + L".tga");

	TextureManager::Load(Name, tmp.c_str());
	FontTexture = TextureManager::Get(Name);

	XMLtoCollection(std::string(ws.begin(), ws.end()) +".xml");

}

void SpriteFont::XMLtoCollection(std::string path) {
	rapidxml::file<char> FontData(path.c_str());

	using namespace rapidxml;
	xml_document<> doc;
	doc.parse<0>(FontData.data());

	size = FontData.size();

	imgArray = new Image*[FontData.size()]{ nullptr };

	xml_node<>* node = doc.first_node();
	while (node != nullptr)
	{
		if (strcmp(node->name(), "fontMetrics") == 0)
		{
			//DebugMsg::out("SpriteFont: font data start for %s\n",
				//node->first_attribute()->value());
			node = node->first_node();
		}
		else if (strcmp(node->name(), "character") == 0)
		{
			//DebugMsg::out("SpriteFont: char data found\n");
			CreateGlyph(node);
			node = node->next_sibling();
		}
	}
}


void SpriteFont::CreateGlyph(rapidxml::xml_node<char>* node)
{
	rapidxml::xml_node<char>* keynode = node;
	Key key = atoi(keynode->first_attribute()->value());

	keynode = keynode->first_node();
	float x = (float)atoi(keynode->value());
	keynode = keynode->next_sibling();
	float y = (float)atoi(keynode->value());
	keynode = keynode->next_sibling();
	float w = (float)atoi(keynode->value());
	keynode = keynode->next_sibling();
	float h = (float)atoi(keynode->value());


	imgArray[key] = new Image(FontTexture, new Rect(x, y, w, h));
	fontmap[key] = SpriteFactory::CreateSprite(SceneName::Scene1, imgArray[key]);
}

SpriteFont::Glyph* SpriteFont::GetGlyph(char c) {

	return fontmap[static_cast<int>(c)];

}