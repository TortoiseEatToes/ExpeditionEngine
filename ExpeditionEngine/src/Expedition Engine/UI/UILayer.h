#pragma once

class UIElement;

class UILayer
{
public:
	UILayer() = delete;
	UILayer(const UILayer& other) = delete;
	UILayer& operator= (const UILayer& other) = delete;
	~UILayer() = default;

	void Draw();

private:
	UIElement* pCurrentElement;
};