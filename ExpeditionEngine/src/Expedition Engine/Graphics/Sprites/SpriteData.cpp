#include "SpriteData.h"
#include "../Image/ImageManager.h"
#include "../Model/Managers/ModelManager.h"
#include "../Image/Rect.h"
#include "../../Scenes/SceneManager.h"
#include "../../Scenes/Scene.h"
#include "../Image/Image.h"

SpriteData::SpriteData()
{
}

void SpriteData::Initialize(SceneName sceneToExistIn, Image* inImg) {
	image = inImg;
	angle = 0;
	centerX = origPosX;
	centerY = origPosY;
	scaleX = 1;
	scaleY = 1;
	layer = 1;

	rect = Rect(origPosX, origPosY, image->pImageRect->width, image->pImageRect->height);

	//pGObj_Sprite = new GraphicObject_Sprite(sceneToExistIn ,img, &rect, 1);


	Scale = Matrix4F(SCALE, scaleX, scaleY, 1.0f);
	RotZ = Matrix4F(IDENTITY);
	Pos = Vector4F(origPosX, origPosY, 1.0f, 1);

	Matrix4F world = (Scale * RotZ).TransposeCopy();
	world *= Matrix4F(TRANS, Pos);

	world.Transpose();

	//pGObj_Sprite->SetWorld(world,0);
}

SpriteData::~SpriteData()
{
	//delete pGObj_Sprite;
}


Matrix4F SpriteData::GetWorld() {

	Scale = Matrix4F(SCALE, scaleX, scaleY, 1.0f);
	//RotZ = Matrix(ROT_Z, angle);

	Matrix4F world = ((Matrix4F(TRANS, Vector4F(centerX, centerY, 0, 0) + (Pos - Vector4F(centerX, centerY, 0, 0)))) * RotZ).TransposeCopy();
	world *= Scale;
	//world.Transpose();
	world[f15] = 1;
	world[f14] = layer;

	return world;
}



void SpriteData::SetCenter(const float& offsetx, const float& offsety) {

	centerX = Pos.X() + offsetx;
	centerY = Pos.Y() + offsety;

}

void SpriteData::SetPosition(const float& x, const float& y) {

	centerX -= Pos.X();
	centerY -= Pos.Y();

	Pos.Set(x, y, layer, 1);

	centerX += x;
	centerY += y;

}

void SpriteData::SetScaleFactor(const float& scalex, const float& scaley) {
	scaleX = scalex;
	scaleY = scaley;
}

void SpriteData::SetScalePixel(const float& width, const float& height) {
	//pGObj_Sprite->origHeight = height;
	//pGObj_Sprite->origWidth = width;
}