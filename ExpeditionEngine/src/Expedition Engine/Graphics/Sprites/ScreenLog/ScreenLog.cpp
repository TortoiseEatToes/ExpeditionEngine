//#include "ScreenLog.h"
//
//#include <cstdio>
//#include <cstdarg>
//#include "../SpriteString.h"
//#include "../Manager/SpriteFontManager.h"
//#include "../SpriteFactory/SpriteStringFactory.h"
//#include "../../../Engine/ExpeditionEngine.h"
//
//ScreenLog* ScreenLog::ptrInstance = nullptr;
//
//char ScreenLog::DebugBuff[] = { 0 };
//
//ScreenLog::ScreenLog() : 
//	//anchorX(0), anchorY(0)
//	anchorX(static_cast<int>(ExpeditionEngine::GetWidth()/2)-50), anchorY(static_cast<int>(ExpeditionEngine::GetHeight() / 2) - 50)
//{
//	//font = SpriteFontManager::Get("TankFont");
//}
//
//
//ScreenLog::~ScreenLog()
//{
//
//}
//
//void ScreenLog::Render() {
//
//	SpriteString* string;
//	int x = anchorX;
//	int y = anchorY;
//	MessageCollection::Iterator it;
//
//	while (messages.GetSize()!=0) {
//	
//		string = SpriteStringFactory::CreateSpriteString();
//
//		messages.SetFront(it);
//
//		string->Set(font, it.GetCurrentObject(), x, y);
//
//		string->Render();
//
//		y -= string->GetHeight() - 5;
//
//		SpriteStringFactory::RecycleSpriteString(string);
//
//		messages.PopFront();
//	}
//
//}
//
//void ScreenLog::Terminate() {
//	delete ptrInstance;
//	ptrInstance = nullptr;
//}
//
//void ScreenLog::Add(char* A, ...) {
//	va_list args;
//	va_start(args, A);
//
//	vsprintf_s(DebugBuff, A, args);
//
//	std::string s(DebugBuff);
//	Instance().messages.PushBack(s);
//
//}