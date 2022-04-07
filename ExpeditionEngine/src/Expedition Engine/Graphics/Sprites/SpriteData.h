#ifndef SpriteData_h
#define SpriteData_h

#include <string>
#include "../../Math/Matrix/Matrix4F.h"
#include "../../Math/Vector/Vector4F.h"
#include "../Image/Rect.h"
#include "../Image/Image.h"

class Camera;
enum SceneName;

class SpriteData : public Align16
{
public:
	SpriteData();
	~SpriteData();
	SpriteData& operator = (const SpriteData&) = delete;
	SpriteData(const SpriteData&) = delete;
	void Initialize(SceneName sceneToExistIn, Image* img);

	float GetAngle() { return angle; }
	int GetWidth(float width) { return static_cast<int>(scaleX * width); }
	int GetHeight(float height) { return static_cast<int>(scaleY * height); }
	Matrix4F GetWorld();
	void SetAngle(const float& a) {angle = 2 * 3.14159f*a/360; }
	void SetCenter(const float& offsetx, const float& offsety);
	void SetPosition(const float& x, const float& y);
	void SetScaleFactor(const float& scalex, const float& scaley);
	void SetScalePixel(const float& width, const float& height);
	void SetLayer(const float& l) { layer = l; }
	Image* GetImage() { return image;}
	Rect& GetRect() { return rect; }

private:

	float angle;
	float centerX;
	float centerY;
	float scaleX;
	float scaleY;
	float layer;

	const float origPosX = 0;
	const float origPosY = 0;

	Matrix4F RotZ;
	Matrix4F Scale;
	Vector4F Pos;
	Rect rect;
	Image* image;
};

#endif SpriteData_h