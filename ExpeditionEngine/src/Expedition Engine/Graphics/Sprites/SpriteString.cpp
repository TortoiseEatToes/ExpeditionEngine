//#include "SpriteString.h"
//#include "SpriteFont.h"
//#include "./../GraphicsObjects/GraphicsObject_Sprite.h"
//
//char SpriteString::DebugBuff[] = { 0 };
//
//SpriteString::SpriteString()
//{
//	//Default Constructor MUST exist because of pooling
//}
//
//SpriteString::SpriteString(SceneName sceneToExistIn, SpriteFont* font) {
//	pFont = font;
//
//	sceneName = sceneToExistIn;
//
//}
//
//
//SpriteString::SpriteString(SceneName sceneToExistIn, SpriteFont* font, std::string str, int x, int y) {
//
//	sceneName = sceneToExistIn;
//	Set(font, str, x, y);
//}
//
//SpriteString::~SpriteString()
//{
//	ClearList();
//}
//
//void SpriteString::ClearList()
//{
//	GlyphCollection::Iterator it;
//
//	glyphs.SetFront(it);
//
//	GraphicsObject_Sprite* tmp;
//
//	while (!it.IsOutOfNodes()) {
//
//		tmp = static_cast<GraphicsObject_Sprite*>(&it.GetCurrentObject());
//
//		//GraphicsObjectManager::ReleaseGraphicObject(tmp);
//		//TODO: SARA NEEDS TO FIX THIS
//		++it;
//	}
//
//	glyphs.Clear();
//}
//
//
//void SpriteString::Set(const int& x, const int& y) {
//
//	posX = x;
//	posY = y;
//
//}
//
//
//void SpriteString::Set(SpriteFont* font, std::string str, int x, int y) 
//{
//	ClearList();
//
//	if (str.length() > 0)
//	{
//		height = 0;
//		width = 0;
//
//		pFont = font;
//
//		posX = x;
//		posY = y;
//
//		Glyph* pGlyph;
//
//		float widthX = static_cast<float>(x);
//
//		//Create the first glyph
//		//GraphicsObjectManager::AquireGraphicObject(pGlyph, sceneName, pFont->GetGlyph(str.at(0)));
//		//TODO: SARA NEEDS TO FIX THIS
//		glyphs.PushBack(*pGlyph);
//
//		//Set it's position
//		pGlyph->SetPosition(widthX, static_cast<float>(posY));
//		widthX += pGlyph->GetWidth() * 0.5f;
//
//		//Create all of the nodes after the first
//		for (int i = 1; i < static_cast<int>(str.length()); i++)
//		{
//			//Create next glyph
//			//GraphicsObjectManager::AquireGraphicObject(pGlyph, sceneName, pFont->GetGlyph(str.at(i)));
//			//TODO: SARA NEEDS TO FIX THIS
//			glyphs.PushBack(*pGlyph);
//			widthX += pGlyph->GetWidth() * 0.5f;
//
//			pGlyph->SetPosition(widthX, static_cast<float>(posY));
//			widthX += pGlyph->GetWidth() * 0.5f;
//		}
//	}
//}
//
//void SpriteString::Set(std::string str) {
//
//	ClearList();
//
//	Glyph* pGlyph;
//
//	for (int i = 0; i < static_cast<int>(str.length()); i++) {
//
//		//GraphicsObjectManager::AquireGraphicObject(pGlyph, sceneName, pFont->GetGlyph(str.at(i)));
//		//TODO: SARA NEEDS TO FIX THIS
//
//		glyphs.PushBack(*pGlyph);
//
//	}
//
//
//}
//
//void SpriteString::SetFormat(char* A, ...) {
//	va_list args;
//	va_start(args, A);
//
//	vsprintf_s(DebugBuff, A, args);
//
//	std::string str(DebugBuff);
//
//	ClearList();
//
//	Glyph* pGlyph;
//
//	for (int i = 0; i < static_cast<int>(str.length()); i++) {
//
//		//GraphicsObjectManager::AquireGraphicObject(pGlyph, sceneName, pFont->GetGlyph(str.at(i)));
//		//TODO: SARA NEEDS TO FIX THIS
//		glyphs.PushBack(*pGlyph);
//
//	}
//}
//
//void SpriteString::SetLayer(const LayerName& layer) {
//	GlyphCollection::Iterator it;
//	glyphs.SetFront(it);
//
//	while (!it.IsOutOfNodes()) {
//		it.GetCurrentObject().SetLayer(layer);
//		++it;
//	}
//}
//
//void SpriteString::StartDrawing(){
//
//	GlyphCollection::Iterator it;
//	glyphs.SetFront(it);
//
//	while (!it.IsOutOfNodes()) {
//		it.GetCurrentObject().StartDrawing();
//		++it;
//	}
//}
//
//void SpriteString::StopDrawing(){
//	GlyphCollection::Iterator it;
//	glyphs.SetFront(it);
//
//	while (!it.IsOutOfNodes()) {
//		it.GetCurrentObject().StopDrawing();
//		++it;
//	}
//}