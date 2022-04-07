#include "SpriteController.h"
#include "../../Expedition Engine/Graphics/Image/ImageManager.h"
#include "../../Expedition Resources/LayerSettings.h"

SpriteController::SpriteController(const SceneName& startingScene)
	: GameObject(startingScene)
{
	//Image* img = ImageManager::Get(ImageName::TestImg1);
	//pSprite1 = new GraphicObject_Sprite(registeredScene, img, img->pImageRect);
	//pSprite1->SetPosition(100, 400);
	//pSprite1->SetLayer(LayerName::LayerBack);
	//pSprite1->SetScaleFactor(10, 10);
	//
	//
	//img = ImageManager::Get(ImageName::TestImg2);
	//pSprite2 = new GraphicObject_Sprite(registeredScene, img, img->pImageRect);
	//pSprite2->SetPosition(300, 400);
	//pSprite2->SetLayer(LayerName::LayerBack);
	//pSprite2->SetScaleFactor(10, 10);
	//
	//img = ImageManager::Get(ImageName::TestImg3);
	//pSprite3 = new GraphicObject_Sprite(registeredScene, img, img->pImageRect);
	//pSprite3->SetPosition(500, 400);
	//pSprite3->SetLayer(LayerName::LayerBack);
	//pSprite3->SetScaleFactor(10, 10);
	//
	//img = ImageManager::Get(ImageName::TestImg4);
	//pSprite4 = new GraphicObject_Sprite(registeredScene, img, img->pImageRect);
	//pSprite4->SetPosition(700, 400);
	//pSprite4->SetLayer(LayerName::LayerBack);
	//pSprite4->SetScaleFactor(10, 10);
	//
	//img = ImageManager::Get(ImageName::TestImg5);
	//pSprite5 = new GraphicObject_Sprite(registeredScene, img, img->pImageRect);
	//pSprite5->SetPosition(900, 400);
	//pSprite5->SetLayer(LayerName::LayerBack);
	//pSprite5->SetScaleFactor(10, 10);
}

SpriteController::~SpriteController() {
	//delete pSprite1;
	//delete pSprite2;
	//delete pSprite3;
	//delete pSprite4;
	//delete pSprite5;
}

void SpriteController::OnSceneEnter() {
	pSprite1->StartDrawing();
	pSprite2->StartDrawing();
	pSprite3->StartDrawing();
	pSprite4->StartDrawing();
	pSprite5->StartDrawing();

	playerControllerSwap1.RegisterForAll(Scene2, Input::LetterKeyG);
	playerControllerSwap1.pSprite = pSprite1;

	playerControllerSwap2.RegisterForAll(Scene2, Input::LetterKeyH);
	playerControllerSwap2.pSprite = pSprite2;

	playerControllerSwap3.RegisterForAll(Scene2, Input::LetterKeyJ);
	playerControllerSwap3.pSprite = pSprite3;

	playerControllerSwap4.RegisterForAll(Scene2, Input::LetterKeyK);
	playerControllerSwap4.pSprite = pSprite4;

	playerControllerSwap5.RegisterForAll(Scene2, Input::LetterKeyL);
	playerControllerSwap5.pSprite = pSprite5;
}

void SpriteController::OnSceneExit() {
	pSprite1->StopDrawing();
	pSprite2->StopDrawing();
	pSprite3->StopDrawing();
	pSprite4->StopDrawing();
	pSprite5->StopDrawing();
}