//#pragma once
//
//#include "UIElement.h"
//#include "../../Graphics/GraphicsObjects/GraphicsObject_Sprite.h"
//#include "../../Containers/List.h"
//
//class Image;
//class Rect;
//
//class Button : public UIElement
//{
//public:
//	Button() = delete;
//	Button(SceneName sceneToExistIn, Image* spriteImage, Rect* rectangle);
//	Button(const Button& other) = delete;
//	Button& operator= (const Button& other) = delete;
//	~Button() = default;
//
//	/// <summary>Display the image and start checking if the button is pressed.</summary>
//	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
//	void StartDrawing(const SceneName& sceneToRegisterTo) override;
//
//	/// <summary>Stop displaying the image and stop checking to see if the button was pressed.</summary>
//	void StopDrawing() override;
//
//	Image* GetImage();
//
//	float GetOrigWidth();
//	float GetOrigHeight();
//
//	float GetOrigPosX();
//	float GetOrigPosY();
//
//	float GetAngle(int instanceID = 0);
//	int GetWidth(int instanceID = 0);
//	int GetHeight(int instanceID = 0);
//	void SetCenter(const float& offsetx, const float& offsety, int instanceID = 0);
//	void SetPosition(const float& x, const float& y, int instanceID = 0);
//	void SetScaleFactor(const float& scalex, const float& scaley, int instanceID = 0);
//	void SetScalePixel(const float& width, const float& height, int instanceID = 0);
//	void SetLayer(const LayerName& layer, int instanceID = 0);
//	void SetLayer(const LayerName& layer) override;
//
//	//Getters for the button's boundaries
//	const float& GetButtonMinX() const { return buttonMinX; }
//	const float& GetButtonMaxX() const { return buttonMaxX; }
//	const float& GetButtonMinY() const { return buttonMinY; }
//	const float& GetButtonMaxY() const { return buttonMaxY; }
//
//
//
//protected:
//	/// <summary>Override this function to define what happens when this button is clicked.</summary>
//	virtual void OnMouseClicked() {}
//
//	/// <summary>Override this function to define what happens when this button is the target of the mouse when it is held.</summary>
//	virtual void OnMouseHeld() {}
//
//	/// <summary>Override this function to define what happens when this button is the target of the mouse when it is released.</summary>
//	virtual void OnMouseReleased() {}
//
//private:
//	friend class ButtonAttorney;
//
//	/// <summary>Overriding SceneComponent function</summary>
//	void RegisterIntoSceneChild(Scene& scene) override;
//	/// <summary>Overriding SceneComponent function</summary>
//	void DeregisterFromSceneChild(Scene& scene) override;
//
//	List<Button>::Iterator& GetIterator() { return iterator; }
//
//	/// <summary>When the sprite gets altered, update the button's boundaries to match them</summary>
//	void UpdateButtonBox();
//
//	GraphicsObject_Sprite* sprite;
//	List<Button>::Iterator iterator;
//
//	//Default to negative numbers to make it easier to see bugs with unassigned values
//	float buttonMinX = -1.0f;
//	float buttonMaxX = -1.0f;
//	float buttonMinY = -1.0f;
//	float buttonMaxY = -1.0f;
//};	
