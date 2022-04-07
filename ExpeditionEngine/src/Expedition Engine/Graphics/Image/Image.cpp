#include "Image.h"
#include "Rect.h"


Image::Image()
{
	pImageRect = nullptr;
}

Image::Image(Texture *pTexture, Rect *pRect) {
	pText = pTexture;
	pImageRect = pRect;
}

void Image::Set(Texture *pTexture, Rect *pRect) {
	pText = pTexture;
	pImageRect = pRect;
}

Image::~Image()
{
	if(pImageRect)
		delete pImageRect;
}
