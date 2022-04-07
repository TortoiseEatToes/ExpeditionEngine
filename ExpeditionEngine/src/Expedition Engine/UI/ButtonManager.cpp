//#include "ButtonManager.h"
//
//ButtonManager::ButtonManager()
//	: mouseLeftButtonTracker(this)
//{
//}
//
//void ButtonManager::MouseLeftButtonPressed()
//{
//	mouseXPosition = mouseLeftButtonTracker.GetMousePositionX();
//	mouseYPosition = mouseLeftButtonTracker.GetMousePositionY();
//
//	activeButtonList.SetFront(iterator);
//	while (!iterator.IsOutOfNodes())
//	{
//		if (mouseXPosition >= iterator.GetCurrentObject().GetButtonMinX() &&
//			mouseXPosition <= iterator.GetCurrentObject().GetButtonMaxX() &&
//			mouseYPosition >= iterator.GetCurrentObject().GetButtonMinY() &&
//			mouseYPosition <= iterator.GetCurrentObject().GetButtonMaxY()   )
//		{
//			ButtonAttorney::ManagerControl::MouseClicked(iterator.GetCurrentObject());
//		}
//		++iterator;
//	}
//}
//
//void ButtonManager::MouseLeftButtonHeld()
//{
//	mouseXPosition = mouseLeftButtonTracker.GetMousePositionX();
//	mouseYPosition = mouseLeftButtonTracker.GetMousePositionY();
//
//	activeButtonList.SetFront(iterator);
//	while (!iterator.IsOutOfNodes())
//	{
//		if (mouseXPosition >= iterator.GetCurrentObject().GetButtonMinX() &&
//			mouseXPosition <= iterator.GetCurrentObject().GetButtonMaxX() &&
//			mouseYPosition >= iterator.GetCurrentObject().GetButtonMinY() &&
//			mouseYPosition <= iterator.GetCurrentObject().GetButtonMaxY())
//		{
//			ButtonAttorney::ManagerControl::MouseHeld(iterator.GetCurrentObject());
//		}
//		++iterator;
//	}
//}
//
//void ButtonManager::MouseLeftButtonReleased()
//{
//	mouseXPosition = mouseLeftButtonTracker.GetMousePositionX();
//	mouseYPosition = mouseLeftButtonTracker.GetMousePositionY();
//
//	activeButtonList.SetFront(iterator);
//	while (!iterator.IsOutOfNodes())
//	{
//		if (mouseXPosition >= iterator.GetCurrentObject().GetButtonMinX() &&
//			mouseXPosition <= iterator.GetCurrentObject().GetButtonMaxX() &&
//			mouseYPosition >= iterator.GetCurrentObject().GetButtonMinY() &&
//			mouseYPosition <= iterator.GetCurrentObject().GetButtonMaxY())
//		{
//			ButtonAttorney::ManagerControl::MouseReleased(iterator.GetCurrentObject());
//		}
//		++iterator;
//	}
//}
//
//void ButtonManager::RegisterButton(Button* pButton)
//{
//	activeButtonList.PushBack(*pButton, ButtonAttorney::ManagerControl::GetIterator(*pButton));
//}
//
//void ButtonManager::DeregisterButton(Button* pButton)
//{
//	activeButtonList.Remove(ButtonAttorney::ManagerControl::GetIterator(*pButton));
//}
//
//void ButtonManager::Initialize(const SceneName& sceneName)
//{
//	mouseLeftButtonTracker.SetButtonManager(this);
//	mouseLeftButtonTracker.RegisterForAll(sceneName, Input::Mouse::LeftButton);
//}
