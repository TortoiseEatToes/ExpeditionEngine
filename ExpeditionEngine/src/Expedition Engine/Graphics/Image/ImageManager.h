#ifndef ImageManager_h
#define ImageManager_h

#include "../Image/Image.h"
#include "../../../Expedition Resources/ImageSettings.h"

class Texture;

/// \ingroup ASSET
/// \{

class ImageManager
{
	friend class ImageManagerAttorney;
private:

	ImageManager();
	~ImageManager();
	ImageManager& operator =(const ImageManager&) = delete;
	ImageManager(const ImageManager&) = delete;

	static ImageManager* ptrInstance;

	static ImageManager& Instance() {
		if (!ptrInstance)
			ptrInstance = new ImageManager;
		return *ptrInstance;
	}

	Image* privGet(const ImageName& key);
	Image* privLoad(const ImageName& key, Texture* tex);
	Image* privLoad(const ImageName& key, Texture* tex, Rect* rec);

	const char* defaultPath = "Images/";

	Image* imageArray;

	static void Initialize() {};
	static void Terminate();

public:
	///\ingroup ASSET
	static Image* Get(const ImageName& key) { return Instance().privGet(key); }

	/// \ingroup ASSET
	static Image* Load(const ImageName& key, Texture* tex) { return Instance().privLoad(key, tex); }

	/// \ingroup ASSET
	static Image* Load(const ImageName& key, Texture* tex, Rect* rec) { return Instance().privLoad(key, tex, rec); }
};
/// \}
#endif ImageManager_h