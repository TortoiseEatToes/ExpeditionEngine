#include "UIScreen.h"

#include "UILayer.h"

void UIScreen::Draw()
{
	pActiveLayer->Draw();
}
