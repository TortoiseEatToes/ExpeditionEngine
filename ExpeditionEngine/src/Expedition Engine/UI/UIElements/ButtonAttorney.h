//#pragma once
//
//#include "Button.h"
//
//class ButtonAttorney
//{
//public:
//	class ManagerControl
//	{
//	private:
//		friend class ButtonManager;
//
//		/// <summary>Call the OnMouseClicked function on this button.</summary>
//		/// <param name="button">Reference to the relevant button</param>
//		static void MouseClicked(Button& button)
//		{
//			button.OnMouseClicked();
//		}
//
//		/// <summary>Call the OnMouseHeld function on this button.</summary>
//		/// <param name="button">Reference to the relevant button</param>
//		static void MouseHeld(Button& button)
//		{
//			button.OnMouseHeld();
//		}
//
//		/// <summary>Call the OnMouseReleased function on this button.</summary>
//		/// <param name="button">Reference to the relevant button</param>
//		static void MouseReleased(Button& button)
//		{
//			button.OnMouseReleased();
//		}
//
//		/// <summary>This getter is used for managing the insertion and removal of this button into the activeButtonList.</summary>
//		/// <param name="button">Reference to the relevant buttonakca</param>
//		static List<Button>::Iterator& GetIterator(Button& button)
//		{
//			return button.GetIterator();
//		}
//	};
//};