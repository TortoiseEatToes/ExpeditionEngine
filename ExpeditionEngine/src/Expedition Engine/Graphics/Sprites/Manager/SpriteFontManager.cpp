#include "SpriteFontManager.h"
#include "../SpriteFont.h"
#include "../SpriteFactory/SpriteFactory.h"
#include "../SpriteFactory/SpriteStringFactory.h"
#include "../../../../Expedition Resources/FontSettings.h"

SpriteFontManager* SpriteFontManager::ptrInstance = nullptr;

SpriteFontManager::SpriteFontManager()
{
	fontArray = new SpriteFont*[NumberOfFonts];

	for (int i = 0; i < NumberOfFonts; i++) {
		fontArray[i] = 0;
	}
}

void SpriteFontManager::Initialize() {
	//Load(FontName::Font1, L"TankFont");
}

SpriteFontManager::~SpriteFontManager()
{
	for (int i = 0; i < NumberOfFonts; i++) {
		if (fontArray[i])
			delete fontArray[i];
	}

	delete[] fontArray;

	SpriteFactory::Terminate();
}

SpriteFont* SpriteFontManager::privLoad(FontName key, TextureName tex, const wchar_t* path) {

	if (fontArray[key]) {
		delete fontArray[key];
	}

	fontArray[key] = new SpriteFont(tex, path);
	return fontArray[key];
}

SpriteFont* SpriteFontManager::privGet(FontName key) {
	return fontArray[key];
}


wchar_t * SpriteFontManager::addDefaultPath(const wchar_t* path) {

	const int BUFFER_SIZE = 100;

	//assert(strlen(path) + strlen(defaultPath) < BUFFER_SIZE - 1);

	wchar_t* tmp = new wchar_t[BUFFER_SIZE];

	wcscpy_s(tmp, BUFFER_SIZE, defaultPath);

	wcscat_s(tmp, BUFFER_SIZE, path);

	return tmp;
}

void SpriteFontManager::Terminate() {
	SpriteFactory::Terminate();
	SpriteStringFactory::Terminate();


	delete ptrInstance;
	ptrInstance = nullptr;
}