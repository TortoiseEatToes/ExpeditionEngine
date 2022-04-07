#ifndef ScreenLog_h
#define ScreenLog_h

#include "../../../Containers/List.h"
#include <string>

class SpriteFont;

class ScreenLog
{
	friend class ScreenLogAttorney;
private:

	static ScreenLog* ptrInstance;

	ScreenLog();
	~ScreenLog();
	ScreenLog(const ScreenLog&) = delete;
	ScreenLog(ScreenLog&&) = delete;
	ScreenLog& operator = (const ScreenLog&) = delete;
	ScreenLog& operator = (ScreenLog&&) = delete;

	static ScreenLog& Instance() {
		if (!ptrInstance)
			ptrInstance = new ScreenLog;
		return *ptrInstance;
	}

	const int anchorX;
	const int anchorY;
	
	static const int BUFF_SIZE = 256;
	static char DebugBuff[BUFF_SIZE];

	SpriteFont* font;

	using MessageCollection = List<std::string>;

	MessageCollection messages;
	void Render();

	static void Terminate();

public:

	static void Add(char* A, ...);

};

#endif ScreenLog_h