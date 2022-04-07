#include "ImageManager.h"
#include <assert.h>
#include "Rect.h"

ImageManager* ImageManager::ptrInstance = nullptr;

ImageManager::ImageManager()
{
	imageArray = new Image[NumberOfImages];
}


ImageManager::~ImageManager()
{
	delete[] imageArray;
}

Image* ImageManager::privGet(const ImageName& key) {
	return &imageArray[key];
}

Image* ImageManager::privLoad(const ImageName& key, Texture* tex) {

	imageArray[key].Set(tex, new Rect(0, 0, static_cast<float>(tex->getWidth()), static_cast<float>(tex->getHeight())));
	return &imageArray[key];
}

Image* ImageManager::privLoad(const ImageName& key, Texture* tex, Rect* rec) {
	imageArray[key].Set(tex, rec);
	return &imageArray[key];

}

void ImageManager::Terminate() {

	delete ptrInstance;
	ptrInstance = nullptr;

}
