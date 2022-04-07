#ifndef SpriteFontManager_h
#define SpriteFontManager_h

class SpriteFont;
enum FontName;
enum SceneName;
enum TextureName;

/// \ingroup ASSET
/// \{

class SpriteFontManager
{
	friend class SpriteFontManagerAttorney;
private:

	SpriteFontManager();
	~SpriteFontManager();
	SpriteFontManager& operator =(const SpriteFontManager&) = delete;
	SpriteFontManager(const SpriteFontManager&) = delete;

	static SpriteFontManager* ptrInstance;

	static SpriteFontManager& Instance() {
		if (!ptrInstance)
			ptrInstance = new SpriteFontManager;
		return *ptrInstance;
	}

	SpriteFont* privGet(FontName key);
	SpriteFont* privLoad(FontName key, TextureName tex, const wchar_t* path);

	const wchar_t* defaultPath = L"Fonts/";
	SpriteFont** fontArray;

	wchar_t * addDefaultPath(const wchar_t* path);

	static void Initialize();
	static void Terminate() ;

public:

	/// \ingroup ASSET
	static SpriteFont* Get(FontName key) { return Instance().privGet(key); }


	/// \ingroup ASSET
	static SpriteFont* Load(FontName key, TextureName tex, const wchar_t* path) { return Instance().privLoad(key, tex, path); }
};
/// \}
#endif SpriteFontManager_h