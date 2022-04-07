//#include "Button.h"
//
//#include "../../Scenes/SceneAttorney.h"
//
//Button::Button(SceneName sceneToExistIn, Image* spriteImage, Rect* rectangle)
//	: iterator()
//{
//	//GraphicsObjectManager::AquireGraphicObject(sprite, sceneToExistIn, spriteImage, rectangle, 1);
//	//TODO: SARA NEEDS TO FIX THIS
//	registeredScene = sceneToExistIn;
//	UpdateButtonBox();
//}
//
//void Button::StartDrawing(const SceneName& sceneToRegisterTo)
//{
//	sprite->StartDrawing();
//	RegisterIntoScene();
//}
//
//void Button::StopDrawing()
//{
//	sprite->StopDrawing();
//	DeregisterFromScene();
//}
//
//Image* Button::GetImage()
//{
//	return sprite->GetImage();
//}
//
//float Button::GetOrigWidth()
//{
//	return sprite->GetOriginWidth();
//}
//
//float Button::GetOrigHeight()
//{
//	return sprite->GetOriginHeight();
//}
//
//float Button::GetOrigPosX()
//{
//	return sprite->GetOriginPositionX();
//}
//
//float Button::GetOrigPosY()
//{
//	return sprite->GetOriginPositionY();
//}
//
//float Button::GetAngle(int instanceID)
//{
//	return sprite->GetAngle(instanceID);
//}
//
//int Button::GetWidth(int instanceID)
//{
//	return sprite->GetWidth(instanceID);
//}
//
//int Button::GetHeight(int instanceID)
//{
//	return sprite->GetHeight(instanceID);
//}
//
//void Button::SetCenter(const float& offsetx, const float& offsety, int instanceID)
//{
//	sprite->SetPosition(offsetx, offsety, instanceID);
//	UpdateButtonBox();
//}
//
//void Button::SetPosition(const float& x, const float& y, int instanceID)
//{
//	sprite->SetPosition(x, y, instanceID);
//	UpdateButtonBox();
//}
//
//void Button::SetScaleFactor(const float& scalex, const float& scaley, int instanceID)
//{
//	sprite->SetScaleFactor(scalex, scaley, instanceID);
//	UpdateButtonBox();
//}
//
//void Button::SetScalePixel(const float& width, const float& height, int instanceID)
//{
//	sprite->SetScalePixel(width, height, instanceID);
//	UpdateButtonBox();
//}
//
//void Button::SetLayer(const LayerName& layer, int instanceID)
//{
//	sprite->SetLayer(layer, instanceID);
//}
//
//void Button::SetLayer(const LayerName& layer)
//{
//	sprite->SetLayer(layer);
//}
//
//void Button::RegisterIntoSceneChild(Scene& scene)
//{
//	SceneAttorney::Getters::GetButtonManager(&scene)->RegisterButton(this);
//}
//
//void Button::DeregisterFromSceneChild(Scene& scene)
//{
//	SceneAttorney::Getters::GetButtonManager(&scene)->DeregisterButton(this);
//}
//
//void Button::UpdateButtonBox()
//{
//	//float halfWidth = (sprite.GetWidth() * 0.5f);
//	//buttonMinX = sprite.GetXPosition() - halfWidth;
//	//buttonMaxX = sprite.GetXPosition() + halfWidth;
//	//
//	//float halfHeight = (sprite.GetHeight() * 0.5f);
//	//buttonMinY = sprite.GetYPosition() - halfHeight;
//	//buttonMaxY = sprite.GetYPosition() + halfHeight;
//
//	buttonMinX = sprite->GetXPosition();
//	buttonMaxX = sprite->GetXPosition() + sprite->GetWidth();
//
//	buttonMinY = sprite->GetYPosition() - sprite->GetHeight();
//	buttonMaxY = sprite->GetYPosition();
//
//}
