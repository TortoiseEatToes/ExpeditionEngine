#ifndef Image_h
#define Image_h

#include "../Model/Texture.h"

class Rect;

class Image
{
public:
	// public methods: -------------------------------------------------------------
	Image();
	Image(Texture *pTexture, Rect *pRect);
	void Set(Texture *pTexture, Rect *pRect);
	~Image();

public:
	// data: -----------------------------------------------------------------------
	Rect		*pImageRect;
	Texture		*pText;
};

#endif Image_h