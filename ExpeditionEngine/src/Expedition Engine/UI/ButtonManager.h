//#pragma once
//
//#include "MouseLeftButtonTracker.h"
//#include "../Containers/List.h"
//#include "UIElements/ButtonAttorney.h"
//
//enum SceneName;
//
//class ButtonManager
//{
//public:
//	ButtonManager();
//	ButtonManager(const ButtonManager& other) = delete;
//	ButtonManager& operator= (const ButtonManager& other) = delete;
//	~ButtonManager() = default;
//
//	/// <summary>Once the scene that owns this manager has finished it's constructor, it will call this so that the mouseLeftButtonTracker can be registered.</summary>
//	/// <param name="sceneToRegisterInto">The SceneName that this manager is owned by</param>
//	void RegisterButton(Button* pButton);
//
//	/// <summary>Once the scene that owns this manager has finished it's constructor, it will call this so that the mouseLeftButtonTracker can be registered.</summary>
//	/// <param name="sceneToRegisterInto">The SceneName that this manager is owned by</param>
//	void DeregisterButton(Button* pButton);
//
//	/// <summary>Once the scene that owns this manager has finished it's constructor, it will call this so that the mouseLeftButtonTracker can be registered.</summary>
//	/// <param name="sceneToRegisterInto">The SceneName that this manager is owned by</param>
//	void Initialize(const SceneName& sceneName);
//
//	/// <summary>This function is called by the MouseLeftButtonTracker when the left mouse button is pressed.</summary>
//	void MouseLeftButtonPressed();
//
//	/// <summary>This function is called by the MouseLeftButtonTracker when the left mouse button is held.</summary>
//	void MouseLeftButtonHeld();
//
//	/// <summary>This function is called by the MouseLeftButtonTracker when the left mouse button is released.</summary>
//	void MouseLeftButtonReleased();
//
//private:
//
//	List<Button> activeButtonList;
//	List<Button>::Iterator iterator;
//	MouseLeftButtonTracker mouseLeftButtonTracker;
//	
//	//These two are here to make it easier to debug mouse events
//	int mouseXPosition = -1;
//	int mouseYPosition = -1;
//};